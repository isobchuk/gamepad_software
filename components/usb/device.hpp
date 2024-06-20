#pragma once

#include <usb.hpp>

namespace iso::usb {
template <> class CUsb<EConnection::Device> {
  static constexpr auto _Connection = EConnection::Device;
  const descriptor::EDeviceClass _DeviceClass;
  const descriptor::EBcdUsb _ProtocolVersion;
  const Type::Word _Vid;
  const Type::Word _Pid;

  const descriptor::UDeviceDescriptor _DeviceDescriptor;

public:
  consteval CUsb(const descriptor::EDeviceClass device, const descriptor::EBcdUsb version, const Type::Word vid, const Type::Word pid)
      : _DeviceClass(device), _ProtocolVersion(version), _Vid(vid), _Pid(pid), _DeviceDescriptor(version, device, vid, pid) {}
};

using UsbDevice = Usb<EConnection::Device>;

} // namespace iso::usb