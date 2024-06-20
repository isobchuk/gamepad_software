#include "config.hpp"

#include "device.hpp"
#include "fifo.hpp"
#include <utility>

#include "request.hpp"

using namespace gamepad;

using namespace iso::usb;

int main() {

  static constexpr UsbDevice usb(descriptor::EDeviceClass::HumanInterfaceDevice, descriptor::EBcdUsb::Usb2_0, 0x5555U, 0x6789U);

  processor::interrupt.GlobalEnable();
  processor::clock.Init();
  processor::gpio.Init();
  processor::systemTimer.Init();
  processor::usb.Init();

  processor::interrupt[iso::meta_type::const_v<stm32f0x0::interrupt::Number::USB>].Enable();

  Timeout timeoutLed;

  while (true) {
    constexpr iso::usb::request::CStandardRequest request{};

    if (processor::usb.Read()) {
      request.Request(processor::usb.Read().aBuffer);
      processor::usb.Read().sLength = 0;
    }

    time.Start(timeoutLed);
    if (time.Check(timeoutLed, 250U)) {
      led.Change();
    }
  }
  return 0;
}
