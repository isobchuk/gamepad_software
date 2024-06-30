#pragma once

#include "descriptor.hpp"

namespace iso::usb {

template <const EConnection conn, typename TIntegration> class CUsb {

  const TIntegration &_Integration;

public:
  consteval CUsb(const TIntegration &integ) : _Integration(integ) {}
};

template <const EConnection conn, typename TIntegration> using Usb = CUsb<conn, TIntegration>;

} // namespace iso::usb