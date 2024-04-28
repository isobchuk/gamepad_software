#pragma once

#include "usb.hpp"

namespace iso::usb::request {

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
    constexpr SRequest(const RequestType requestType, const ERequest request, const Type::Word value, const Type::Word index, const Type::Word length)
        : bmRequestType(requestType), bRequest(request), wValue(value), wIndex(index), wLength(length) {}
  };

  using Request = SRequest;
  const Request rRequest;
  const Type::Byte rBuffer[sizeof(rRequest)];

  constexpr UStandardRequest() : rBuffer() {}
  constexpr UStandardRequest(const char (&buff)[sizeof(rRequest)])
      : rBuffer{buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], buff[6], buff[7]} {}
  constexpr UStandardRequest(const Request::RequestType requestType, const ERequest request, const Type::Word value, const Type::Word index,
                             const Type::Word length)
      : rRequest(requestType, request, value, index, length) {}
};

using StandardRequest = UStandardRequest;
static_assert(8 == sizeof(StandardRequest), "The standard request length should be equal to 8 (USB 2.0 spec)");
}; // namespace iso::usb::request