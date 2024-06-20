#pragma once

#include "type.hpp"
#include <bit>
#include <endpoint.hpp>

namespace iso::usb::request {

class CStandardRequest {
  static constexpr unsigned _STANDARD_REQUEST_SIZE = 8U;

  union UStandardRequest {

    enum class ERequest : Type::Byte {
      GET_STATUS,
      CLEAR_FEATURE,
      SET_FEATURE = 0x03U,
      SET_ADDRESS = 0x05U,
      GET_DESCRIPTOR,
      SET_DESCRIPTOR,
      GET_CONFIGURATION,
      SET_CONFIGURATION,
      GET_INTERFACE,
      SET_INTERFACE,
      SYNCH_FRAME,
      SET_LINE_CODING = 0x20U,
      GET_LINE_CODING,
      SET_CONTROL_LINE_STATE,
      GET_MAX_LUN = 0xFEU,
      BULK_ONLY_MSD_RESET,
    };

    struct SRequest {
      union UBmRequestType {
        struct SBitMap {
          enum class ERecipient : Type::BitMap<Type::Byte> { Device, Interface, Endpoint, Other };
          enum class EType : Type::BitMap<Type::Byte> { Standard, Class, Vendor, Reserved };
          enum class EDataTransferDirection : Type::BitMap<Type::Byte> { Host2Device, Device2Host };
          const ERecipient bmRecipient : 5;
          const EType bmType : 2;
          const EDataTransferDirection bmDataTransferDirection : 1;

          constexpr SBitMap() : bmRecipient(), bmType(), bmDataTransferDirection() {}
          constexpr SBitMap(const ERecipient recipient, const EType type, const EDataTransferDirection direction)
              : bmRecipient(recipient), bmType(type), bmDataTransferDirection(direction) {}
        };

        using BitMap = SBitMap;

        const BitMap bmCharacteristics;
        const Type::BitMap<Type::Byte> bmBuffer;

        constexpr UBmRequestType() : bmBuffer() {}
        constexpr UBmRequestType(const Type::BitMap<Type::Byte> buffer) : bmBuffer(buffer) {}
        constexpr UBmRequestType(const BitMap::ERecipient recipient, const BitMap::EType type, const BitMap::EDataTransferDirection direction)
            : bmCharacteristics(recipient, type, direction) {}
      };

      using RequestType = UBmRequestType;

      const RequestType bmRequestType;
      const ERequest bRequest;
      const Type::Word wValue;
      const Type::Word wIndex;
      const Type::Word wLength;

      constexpr SRequest() : bmRequestType(), bRequest(), wValue(), wIndex(), wLength() {}
      constexpr SRequest(const RequestType requestType, const ERequest request, const Type::Word value, const Type::Word index,
                         const Type::Word length)
          : bmRequestType(requestType), bRequest(request), wValue(value), wIndex(index), wLength(length) {}
    };

    using Request = SRequest;
    const Request rRequest;
    const Type::Byte rBuffer[sizeof(rRequest)];

    constexpr UStandardRequest(const Type::Byte (&buff)[sizeof(rRequest)])
        : rRequest(buff[0], static_cast<ERequest>(buff[1]), static_cast<Type::Word>(static_cast<Type::Word>(buff[3]) << 8 | buff[2]),
                   static_cast<Type::Word>(static_cast<Type::Word>(buff[5]) << 8 | buff[4]),
                   static_cast<Type::Word>(static_cast<Type::Word>(buff[7]) << 8 | buff[6])) {}
    constexpr UStandardRequest(const Request::RequestType requestType, const ERequest request, const Type::Word value, const Type::Word index,
                               const Type::Word length)
        : rBuffer{requestType.bmBuffer,
                  static_cast<Type::Byte>(request),
                  static_cast<Type::Byte>(value),
                  static_cast<Type::Byte>(value >> 8),
                  static_cast<Type::Byte>(index),
                  static_cast<Type::Byte>(index >> 8),
                  static_cast<Type::Byte>(length),
                  static_cast<Type::Byte>(length >> 8)} {}
  };

  class CHandler final {
  public:
    /*!<-----Standart request functions------->!*/
    /*static bool get_status(void);
    static bool clear_feature(void);
    static bool set_feature(void);
    static bool set_address(void);*/
    static bool get_descriptor(void);
    /*static bool set_descriptor(void);
    static bool get_configuration(void);
    static bool set_configuration(void);
    static bool get_interface(void);
    static bool set_interface(void);
    static bool synch_frame(void);
    static bool set_line_coding(void);
    static bool get_line_coding(void);
    static bool set_control_line_state(void);
    static bool get_max_lun(void);
    static bool bulk_only_msd_reset(void);*/

    using t_standart_usb_requests_handler = struct s_standart_usb_requests_handler {
      UStandardRequest::ERequest request;
      bool (&current_request_handler)(void);
    };

    static constexpr t_standart_usb_requests_handler standart_usb_requests_handler[] = {
        /*{UStandardRequest::ERequest::GET_STATUS, get_status},
        {UStandardRequest::ERequest::CLEAR_FEATURE, clear_feature},
        {UStandardRequest::ERequest::SET_FEATURE, set_feature},
        {UStandardRequest::ERequest::SET_ADDRESS, set_address},*/
        {UStandardRequest::ERequest::GET_DESCRIPTOR, get_descriptor},
        /*{UStandardRequest::ERequest::SET_DESCRIPTOR, set_descriptor},
        {UStandardRequest::ERequest::GET_CONFIGURATION, get_configuration},
        {UStandardRequest::ERequest::SET_CONFIGURATION, set_configuration},
        {UStandardRequest::ERequest::GET_INTERFACE, get_interface},
        {UStandardRequest::ERequest::SET_INTERFACE, set_interface},
        {UStandardRequest::ERequest::SYNCH_FRAME, synch_frame},
        {UStandardRequest::ERequest::SET_LINE_CODING, set_line_coding},
        {UStandardRequest::ERequest::GET_LINE_CODING, get_line_coding},
        {UStandardRequest::ERequest::SET_CONTROL_LINE_STATE, set_control_line_state},
        {UStandardRequest::ERequest::GET_MAX_LUN, get_max_lun},
        {UStandardRequest::ERequest::BULK_ONLY_MSD_RESET, bulk_only_msd_reset}*/};

    CHandler() = delete;

    inline static bool Handle(const UStandardRequest::ERequest rType) {
      for (const auto &handler : standart_usb_requests_handler)
        if (handler.request == rType) {
          return handler.current_request_handler();
        }
      return false;
    }
  };

public:
  inline CStandardRequest() = default;

  inline bool Request(volatile Type::Byte (&buf)[_STANDARD_REQUEST_SIZE]) const volatile {
    const UStandardRequest request(const_cast<Type::Byte(&)[_STANDARD_REQUEST_SIZE]>(buf));

    return true;
  }
};

}; // namespace iso::usb::request