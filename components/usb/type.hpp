#pragma once

#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>

namespace iso::usb {

namespace Type {
using Byte = uint8_t;
using Word = uint16_t;
using Index = uint8_t;
using Bcd = uint16_t;
using Id = uint16_t;
template <typename Type> using BitMap = Type;
} // namespace Type

class architecture final {
  architecture() = delete;

public:
  template <const size_t N> static consteval size_t size(const Type::Byte (&)[N]) { return N; }

  template <const std::endian end> inline static constexpr bool _check_endian = (end == std::endian::native);

  template <std::unsigned_integral T> inline static constexpr T cast(T val) { return val; }

  template <std::unsigned_integral T>
  requires _check_endian<std::endian::big>
  inline constexpr static T cast(T val) {
    if constexpr (sizeof(Type::Byte) == sizeof(T)) {
      return val;
    } else if (sizeof(Type::Word) == sizeof(T)) {
      return ((val & 0xFFU) << 8) | ((val & 0xFF00) >> 8);
    } else {
      static_assert((sizeof(Type::Word) <= sizeof(T)), "The maximum type size is Type::Word");
    }
  }
};

enum class EConnection { Device, Host, OTG };

enum class EBcdUsb : Type::Word { Usb1_0 = 0x01'00U, Usb1_1 = 0x01'10U, Usb2_0 = 0x02'00U, Usb3_0 = 0x03'00U, Usb3_1 = 0x03'10U, Usb3_2 = 0x03'20U };

enum class EDescriptorType : Type::Byte { Device = 0x1U, Configuration, String, Interface, Endpoint, Qualifier, CustomHid = 0x21U, ReportDescriptor };

enum class EDeviceClass : Type::Byte {
  Unspecified,         // Device class is unspecified, interface descriptors are used to determine needed drivers
  Audio,               // Speaker, microphone, sound card, MIDI
  CommunicationDevice, //
  HumanInterfaceDevice,
  PhysicalInterfaceDevice = 0x05,
  Image,
  Printer,
  MassStorageDevice,
  USBHub,
  CDCData,
  SmartCardReader,
  ContentSecurity = 0x0D,
  VideoDeviceClass,
  PersonalHealthcare,
  DiagnosticsDevice = 0xDC,
  WirelessController = 0xE0,
  Miscellaneous = 0xEF,
  ApplicationSpecific = 0xFE,
  VendorSpecific
};

} // namespace iso::usb