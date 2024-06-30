#pragma once

#include "config.hpp"
#include "descriptor.hpp"
#include "endpoint.hpp"
#include "mcu_usb.hpp"
#include "request.hpp"
#include "system_time.hpp"
#include "type.hpp"

namespace integration::usb::device {

static bool flag;

template <typename TTimer> class CUsbIntegration {
  using SInterruptEndpoint = iso::usb::endpoint::CEndpoint<64U>;
  using TEndpointInterrupt =
      stm32f0x0::usb::Endpoint<SInterruptEndpoint, stm32f0x0::usb::EndpointType::Interrupt, 1UL, stm32f0x0::usb::_MESSAGE_USER_SPACE, 64U>;
  static volatile TEndpointInterrupt EndpointInterrupt;

  static constexpr iso::usb::descriptor::CDescriptorDeviceBuffer _DescriptorDevice{iso::usb::EBcdUsb::Usb2_0, 0xB6AU, 0x146U};

  static constexpr iso::usb::descriptor::CDescriptorInterfaceBuffer _DescriptorInterface{0U, 1U, iso::usb::EDeviceClass::HumanInterfaceDevice, 0U, 0};
  static constexpr iso::usb::descriptor::CDescriptorEndpointBuffer _DescriptorEndpointInterruptIn{iso::usb::endpoint::EType::Interrupt,
                                                                                                  iso::usb::endpoint::EDirection::In, 1U};
  static constexpr iso::usb::descriptor::CDescriptorEndpointBuffer _DescriptorEndpointInterruptOut{iso::usb::endpoint::EType::Interrupt,
                                                                                                   iso::usb::endpoint::EDirection::Out, 1U};
  /*static constexpr uint8_t _DescriptorReport[] = {
      0x05, 0x01, // USAGE_PAGE (Generic Desktop)
      0x09, 0x05, // USAGE (Game Pad)
      0xa1, 0x01, // COLLECTION (Application)
      0xa1, 0x00, //   COLLECTION (Physical)
      // ReportID - 8 bits
      0x85, 0x01, //     REPORT_ID (1)
      // X & Y - 2x8 = 16 bits
      0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
      0x09, 0x30, //     USAGE (X)
      0x09, 0x31, //     USAGE (Y)
      0x15, 0x81, //     LOGICAL_MINIMUM (-127)
      0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
      0x75, 0x08, //     REPORT_SIZE (8)
      0x95, 0x02, //     REPORT_COUNT (2)
      0x81, 0x02, //     INPUT (Data,Var,Abs)
      0xC0,
      // Buttons - 8 bits
      0x05, 0x09, //     USAGE_PAGE (Button)
      0x19, 0x01, //     USAGE_MINIMUM (Button 1)
      0x29, 0x05, //     USAGE_MAXIMUM (Button 8)
      0x15, 0x00, //     LOGICAL_MINIMUM (0)
      0x25, 0x01, //     LOGICAL_MAXIMUM (1)
      0x75, 0x01, //     REPORT_SIZE (8)
      0x95, 0x01, //     REPORT_COUNT (1)
      0x81, 0x02, //     INPUT (Data,Var,Abs)
      0xc0        //     END_COLLECTION
  };
  static constexpr uint8_t _DescriptorReport[] = {
      0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
      0x09, 0x04,       // USAGE (Joystick)
      0xa1, 0x01,       // COLLECTION (Application)
      0x85, 0x01,       //   REPORT_ID (1)
      0xa1, 0x02,       //   COLLECTION (Logical)
      0x09, 0x32,       //     USAGE (Z)
      0x09, 0x31,       //     USAGE (Y)
      0x09, 0x30,       //     USAGE (X)
      0x15, 0x00,       //     LOGICAL_MINIMUM (0)
      0x26, 0xff, 0x00, //     LOGICAL_MAXIMUM (255)
      0x35, 0x00,       //     PHYSICAL_MINIMUM (0)
      0x46, 0xff, 0x00, //     PHYSICAL_MAXIMUM (255)
      0x75, 0x08,       //     REPORT_SIZE (8)
      0x95, 0x03,       //     REPORT_COUNT (3)
      0x81, 0x02,       //     INPUT (Data,Var,Abs)
      0xc0,             //   END_COLLECTION

      0x85, 0x02, // REPORT_ID (2)

      0xa1, 0x02, //   COLLECTION (Logical)
      0x05, 0x09, //     USAGE_PAGE (Button)
      0x29, 0x05, //     USAGE_MAXIMUM (Button 5)
      0x19, 0x01, //     USAGE_MINIMUM (Button 1)
      0x95, 0x05, //     REPORT_COUNT (2)
      0x75, 0x01, //     REPORT_SIZE (1)
      0x25, 0x01, //     LOGICAL_MAXIMUM (1)
      0x15, 0x00, //     LOGICAL_MINIMUM (0)
      0x81, 0x02, //     Input (Data, Variable, Absolute)
      0x95, 0x01, //     Report Count (1)
      0x75, 0x03, //     Report Size (6)
      0x81, 0x01, //     Input (Constant) for padding
      0xc0,       //   END_COLLECTION
      0xc0        // END_COLLECTION
  };*/

  static constexpr uint8_t _DescriptorReport[] = {
      0x05, 0x01, // Usage Page (Generic Desktop)
      0x09, 0x05, // Usage (Game Pad)
      0xA1, 0x01, // Collection (Application)

      0x05, 0x09, //   Usage Page (Button)
      0x19, 0x01, //   Usage Minimum (Button 1)
      0x29, 0x05, //   Usage Maximum (Button 5)
      0x15, 0x00, //   Logical Minimum (0)
      0x25, 0x01, //   Logical Maximum (1)
      0x95, 0x05, //   Report Count (5)
      0x75, 0x01, //   Report Size (1)
      0x81, 0x02, //   Input (Data, Var, Abs)

      0x95, 0x01, //   Report Count (1)
      0x75, 0x03, //   Report Size (3)
      0x81, 0x03, //   Input (Const, Var, Abs)

      0x05, 0x01, //   Usage Page (Generic Desktop)
      0x09, 0x30, //   Usage (X)
      0x09, 0x31, //   Usage (Y)
      0x15, 0x81, //   Logical Minimum (-127)
      0x25, 0x7F, //   Logical Maximum (127)
      0x75, 0x08, //   Report Size (8)
      0x95, 0x02, //   Report Count (2)
      0x81, 0x02, //   Input (Data, Var, Abs)

      0xC0 // End Collection
  };

  static constexpr iso::usb::descriptor::CDescriptorCustomHidBuffer _DescriptorCustomHid{sizeof(_DescriptorReport)};

  static constexpr iso::usb::descriptor::CDescriptorConfigurationBuffer _DescriptorConfiguration{1U, 1U, _DescriptorInterface, _DescriptorCustomHid,
                                                                                                 _DescriptorEndpointInterruptIn};

  static constexpr iso::usb::descriptor::CDescriptorStringBuffer _DescriptorStringSerialNumber{"234562345623456"};
  static constexpr iso::usb::descriptor::CDescriptorStringBuffer _DescriptorStringLanguage{};
  static constexpr iso::usb::descriptor::CDescriptorStringBuffer _DescriptorStringProduct{"Is Game"};
  static constexpr iso::usb::descriptor::CDescriptorStringBuffer _DescriptorStringManufacturer{"Game Controller"};

  // High-Speed info
  static constexpr uint8_t _DescriptorQualifier[] = {
      0x0A, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
  };

public:
  static constexpr stm32f0x0::usb::Usb<EndpointInterrupt> _Hardware{};
  const TTimer &_Timer;
  consteval CUsbIntegration(const TTimer &timer) : _Timer(timer) {}

  inline void Init() const { _Hardware.Init(); }

  inline constexpr auto DeviceDescriptor() const -> const iso::usb::Type::Byte (&)[_DescriptorDevice.size()] { return _DescriptorDevice._Descriptor; }
  inline constexpr auto ConfigurationDescriptor() const -> const iso::usb::Type::Byte (&)[_DescriptorConfiguration.size()] {

    return _DescriptorConfiguration._Descriptor;
  }

  inline constexpr auto StringSerialNumberDescriptor() const -> const iso::usb::Type::Byte (&)[_DescriptorStringSerialNumber.size()] {
    return _DescriptorStringSerialNumber._Descriptor;
  }

  inline constexpr auto StringLanguageDescriptor() const -> const iso::usb::Type::Byte (&)[_DescriptorStringLanguage.size()] {
    return _DescriptorStringLanguage._Descriptor;
  }

  inline constexpr auto StringProductDescriptor() const -> const iso::usb::Type::Byte (&)[_DescriptorStringManufacturer.size()] {
    return _DescriptorStringManufacturer._Descriptor;
  }

  inline constexpr auto StringManufacturerDescriptor() const -> const iso::usb::Type::Byte (&)[_DescriptorStringManufacturer.size()] {
    return _DescriptorStringManufacturer._Descriptor;
  }

  inline constexpr auto QualifierDescriptor() const -> const iso::usb::Type::Byte (&)[sizeof(_DescriptorQualifier)] { return _DescriptorQualifier; }

  inline void SetConfiguration() const {
    EndpointInterrupt.Init();
    /*const uint8_t buttons[] = {0x0, 0x0, 0x0, 0x1};
    EndpointInterrupt.Write(buttons);*/
    flag = true;
  }

  inline constexpr auto CustomHid() const -> const iso::usb::Type::Byte (&)[sizeof(_DescriptorReport)] { return _DescriptorReport; }

  void operator()() const {
    using namespace iso::usb;

    auto &epBuffer = EndpointInterrupt.Read();

    if (epBuffer) {
      // Away from volatile
      Type::Byte buffer[request::_STANDARD_REQUEST_SIZE];
      for (unsigned i = 0; i < sizeof(buffer); i++) {
        buffer[i] = epBuffer.aBuffer[i];
      }

      EndpointInterrupt.Ack();
      epBuffer();
    }
  }

  template <const unsigned N> bool Refresh(const uint8_t (&buf)[N]) const {
    if (flag) {
      return EndpointInterrupt.Write(buf, 3);
    }
    return false;
  }
};

template <typename TTimer> class CUsbIntegration<TTimer>::TEndpointInterrupt volatile CUsbIntegration<TTimer>::EndpointInterrupt;
} // namespace integration::usb::device