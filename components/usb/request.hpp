#pragma once

#include "type.hpp"
#include <bit>
#include <descriptor.hpp>
#include <endpoint.hpp>

static unsigned noHandler;

namespace iso::usb::request {
enum class ERequest : Type::Byte {
  GET_STATUS,
  CLEAR_FEATURE,
  SET_FEATURE = 0x03U,
  SetAddress = 0x05U,
  GetDescriptor,
  SET_DESCRIPTOR,
  GET_CONFIGURATION,
  SetConfiguration,
  GetInterface,
  SET_INTERFACE,
  SYNCH_FRAME,
  SET_LINE_CODING = 0x20U,
  GET_LINE_CODING,
  SET_CONTROL_LINE_STATE,
  GET_MAX_LUN = 0xFEU,
  BULK_ONLY_MSD_RESET,
};

static constexpr unsigned _STANDARD_REQUEST_SIZE = 8U;

struct SRequest {
  struct SBmRequestType {
    enum class ERecipient : Type::BitMap<Type::Byte> { Device, Interface, Endpoint, Other };
    enum class EType : Type::BitMap<Type::Byte> { Standard, Class, Vendor, Reserved };
    enum class EDataTransferDirection : Type::BitMap<Type::Byte> { Host2Device, Device2Host };

    struct SBitMap {
      ERecipient bmRecipient : 5;
      EType bmType : 2;
      EDataTransferDirection bmDataTransferDirection : 1;

      inline constexpr SBitMap() : bmRecipient(), bmType(), bmDataTransferDirection() {}
      inline constexpr SBitMap(const ERecipient recipient, const EType type, const EDataTransferDirection direction)
          : bmRecipient(recipient), bmType(type), bmDataTransferDirection(direction) {}
    };

    using BitMap = SBitMap;

    union {
      BitMap bmCharacteristics;
      Type::Byte bmByte;
    };

    inline constexpr SBmRequestType() : bmCharacteristics() {}
    inline constexpr SBmRequestType(const Type::BitMap<Type::Byte> byte)
        : bmCharacteristics(static_cast<ERecipient>(byte & 0b0001'1111), static_cast<EType>((byte & 0b0110'0000) >> 5),
                            static_cast<EDataTransferDirection>((byte & 0b1000'0000) >> 7)) {}
  };

  using RequestType = SBmRequestType;
  RequestType bmRequestType;
  ERequest bRequest;
  Type::Word wValue;
  Type::Word wIndex;
  Type::Word wLength;

  inline constexpr SRequest() : bmRequestType(), bRequest(), wValue(), wIndex(), wLength() {}
  inline constexpr SRequest(const RequestType requestType, const ERequest request, const Type::Word value, const Type::Word index,
                            const Type::Word length)
      : bmRequestType(requestType), bRequest(request), wValue(value), wIndex(index), wLength(length) {}
};

using Request = SRequest;

class CRequestStandard {
  CRequestStandard() = delete;

public:
  inline static constexpr void Request(const Type::Byte (&buff)[_STANDARD_REQUEST_SIZE], SRequest &request) {
    request.bmRequestType.bmByte = buff[0];
    request.bRequest = static_cast<ERequest>(buff[1]);
    request.wValue = static_cast<Type::Word>(static_cast<Type::Word>(buff[3]) << 8 | buff[2]);
    request.wIndex = static_cast<Type::Word>(static_cast<Type::Word>(buff[5]) << 8 | buff[4]);
    request.wLength = static_cast<Type::Word>(static_cast<Type::Word>(buff[7]) << 8 | buff[6]);
  }

  inline static constexpr void Buffer(const SRequest &request, Type::Byte (&buff)[_STANDARD_REQUEST_SIZE]) {
    buff[0] = request.bmRequestType.bmByte;
    buff[1] = static_cast<Type::Byte>(request.bRequest);
    buff[2] = static_cast<Type::Byte>(request.wValue);
    buff[4] = static_cast<Type::Byte>(request.wValue >> 8);
    buff[5] = static_cast<Type::Byte>(request.wIndex);
    buff[6] = static_cast<Type::Byte>(request.wIndex >> 8);
    buff[7] = static_cast<Type::Byte>(request.wLength);
    buff[8] = static_cast<Type::Byte>(request.wLength >> 8);
  }
};

template <typename TIntegration> class CHandler final {

  const TIntegration &_Integration;

  /*!<-----Standart request functions------->!*/
  bool SetAddress(const SRequest &request) {
    _Integration._Hardware.ControlEndpoint().WriteEmpty();
    _Integration._Timer.Delay(2);
    _Integration._Hardware.Address(static_cast<Type::Byte>(request.wValue));
    return true;
  }
  bool GetDescriptor(const SRequest &request) {
    enum class EStringDescriptor { Language, Manufacturer, Product, SerialNumber };

    switch (static_cast<EDescriptorType>(request.wValue >> 8)) {
    case EDescriptorType::Device:
      if (request.wLength >= sizeof(_Integration.DeviceDescriptor())) {
        _Integration._Hardware.ControlEndpoint().Write(_Integration.DeviceDescriptor());
      } else {
        _Integration._Hardware.ControlEndpoint().Write(_Integration.DeviceDescriptor(), request.wLength);
      };
      break;

    case EDescriptorType::Configuration:

      if (request.wLength >= sizeof(_Integration.ConfigurationDescriptor())) {
        _Integration._Hardware.ControlEndpoint().Write(_Integration.ConfigurationDescriptor());
      } else {
        _Integration._Hardware.ControlEndpoint().Write(_Integration.ConfigurationDescriptor(), request.wLength);
      }
      break;

    case EDescriptorType::String:
      switch (static_cast<EStringDescriptor>((request.wValue) & 0xFF)) {
      case EStringDescriptor::Language:
        _Integration._Hardware.ControlEndpoint().Write(_Integration.StringLanguageDescriptor());
        break;

      case EStringDescriptor::Manufacturer:
        _Integration._Hardware.ControlEndpoint().Write(_Integration.StringManufacturerDescriptor());
        break;

      case EStringDescriptor::Product:
        //_Integration._Hardware.ControlEndpoint().WriteEmpty();
        _Integration._Hardware.ControlEndpoint().Write(_Integration.StringProductDescriptor());
        break;

      case EStringDescriptor::SerialNumber:
        _Integration._Hardware.ControlEndpoint().Write(_Integration.StringSerialNumberDescriptor());
        break;

      default:
        _Integration._Hardware.ControlEndpoint().WriteEmpty();
        noHandler++;
        break;
      }
      break;

    case EDescriptorType::Qualifier:
      _Integration._Hardware.ControlEndpoint().Write(_Integration.QualifierDescriptor());
      break;

    case EDescriptorType::ReportDescriptor:
      _Integration._Hardware.ControlEndpoint().Write(_Integration.CustomHid());
      break;

    default:
      noHandler++;
      break;
    }
    return true;
  }

  bool SetConfiguration(const SRequest &) {
    _Integration.SetConfiguration();
    _Integration._Hardware.ControlEndpoint().WriteEmpty();
    return true;
  }

  bool GetInterface(const SRequest &) { return _Integration._Hardware.ControlEndpoint().WriteEmpty(); }

  struct SStandardRequestTable {
    ERequest request;
    bool (CHandler::*Handler)(const SRequest &request);
  };

  static constexpr SStandardRequestTable _TableStandardRequests[] = {{ERequest::SetAddress, &CHandler::SetAddress},
                                                                     {ERequest::GetDescriptor, &CHandler::GetDescriptor},
                                                                     {ERequest::SetConfiguration, &CHandler::SetConfiguration},
                                                                     {ERequest::GetInterface, &CHandler::GetInterface}};

public:
  inline constexpr CHandler(const TIntegration &integ) : _Integration(integ) {}

  inline bool Handle(const SRequest &request) {
    for (const auto &handler : _TableStandardRequests) {
      if (handler.request == request.bRequest) {
        return (this->*handler.Handler)(request);
      }
    }
    noHandler++;
    return true;
  }
};
} // namespace iso::usb::request
