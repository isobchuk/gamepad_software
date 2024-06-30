#pragma once

#include "request.hpp"
#include "usb.hpp"
static unsigned ctr;

static uint16_t last;

namespace iso::usb {
template <typename TIntegration> class CUsb<EConnection::Device, TIntegration> {

  const TIntegration &_Integration;

public:
  consteval CUsb(const TIntegration &integ) : _Integration(integ) {}
  void Init() const { _Integration.Init(); }
  void operator()() const {
    using namespace iso::usb;

    volatile auto &epBuffer = _Integration._Hardware.ControlEndpoint().Read();

    if (epBuffer) {
      // Away from volatile
      Type::Byte buffer[request::_STANDARD_REQUEST_SIZE];
      for (unsigned i = 0; i < sizeof(buffer); i++) {
        buffer[i] = epBuffer.aBuffer[i];
      }

      ctr++;

      request::SRequest request;
      request::CRequestStandard::Request(buffer, request);
      last = request.wLength;
      _Integration._Hardware.ControlEndpoint().Ack();
      epBuffer();

      auto requestHandler = request::CHandler(_Integration);
      requestHandler.Handle(request);
    }

    _Integration();
  }
};

template <typename TIntegration> using UsbDevice = Usb<EConnection::Device, TIntegration>;

} // namespace iso::usb