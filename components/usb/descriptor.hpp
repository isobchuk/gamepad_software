#pragma once

#include "type.hpp"

namespace iso::usb::descriptor {
enum class EBcdUsb : Type::Word { Usb1_0 = 0x01'00, Usb1_1 = 0x01'10, Usb2_0 = 0x02'00, Usb3_0 = 0x03'00, Usb3_1 = 0x03'10, Usb3_2 = 0x03'20 };

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

union UDeviceDescriptor {
  struct SDeviceDescriptor {
    const Type::Byte bLength;
    const Type::Byte bDescriptorType;
    const EBcdUsb bcdUSB;
    const EDeviceClass bDeviceClass;
    const Type::Byte bDeviceSubClass;
    const Type::Byte bDeviceProtocol;
    const Type::Byte bMaxPacketSize;
    const Type::Word idVendor;
    const Type::Word idProduct;
    const Type::Word bcdDevice;
    const Type::Byte iManufacturer;
    const Type::Byte iProduct;
    const Type::Byte iSerialNumber;
    const Type::Byte bNumConfigurations;

    consteval SDeviceDescriptor(const EBcdUsb usbVersion, const EDeviceClass deviceClass, const Type::Word vendorId, const Type::Word productId)
        : bLength(sizeof(SDeviceDescriptor)), bDescriptorType(0x01), bcdUSB(usbVersion), bDeviceClass(deviceClass), bDeviceSubClass(0x00),
          bDeviceProtocol(0x00), bMaxPacketSize(64), idVendor(vendorId), idProduct(productId), bcdDevice(0x00), iManufacturer(0x01), iProduct(0x02),
          iSerialNumber(0x03), bNumConfigurations(0x01) {}
  };

  const SDeviceDescriptor dDeviceDescriptor;
  const Type::Byte aBuffer[sizeof(dDeviceDescriptor)];

  consteval UDeviceDescriptor(const EBcdUsb usbVersion, const EDeviceClass deviceClass, const Type::Word vendorId, const Type::Word productId)
      : dDeviceDescriptor(usbVersion, deviceClass, vendorId, productId) {}
};

using DeviceDescriptor = UDeviceDescriptor;
static_assert(18 == sizeof(DeviceDescriptor), "The device descriptor size should be 18!");

} // namespace iso::usb::descriptor
