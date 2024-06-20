#pragma once

#include "descriptor.hpp"

namespace iso::usb {

enum class EConnection { Device, Host, OTG };

template <const EConnection conn> class CUsb {
  static constexpr auto _Connection = conn;
  const descriptor::EDeviceClass _DeviceClass;
  const descriptor::EBcdUsb _ProtocolVersion;
  const Type::Word _Vid;
  const Type::Word _Pid;

  const descriptor::UDeviceDescriptor _DeviceDescriptor;

public:
  consteval CUsb(const descriptor::EDeviceClass device, const descriptor::EBcdUsb version, const Type::Word vid, const Type::Word pid)
  requires false
      : _DeviceClass(device), _ProtocolVersion(version), _Vid(vid), _Pid(pid), _DeviceDescriptor(version, device, vid, pid) {}
};

template <const EConnection conn> using Usb = CUsb<conn>;

} // namespace iso::usb