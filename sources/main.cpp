#include "config.hpp"
#include "request.hpp"

using namespace gamepad;

int main() {
  processor::interrupt.GlobalEnable();
  processor::clock.Init();
  processor::gpio.Init();
  processor::systemTimer.Init();
  processor::usb.Init();

  processor::interrupt[iso::meta_type::const_v<stm32f0x0::interrupt::Number::USB>].Enable();

  Timeout timeoutLed;

  while (true) {
    time.Start(timeoutLed);
    if (time.Check(timeoutLed, 250U)) {
      led.Change();
    }
  }
  // using namespace iso::usb::request;
  // static constexpr char buffer[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
  // static constexpr StandardRequest request(buffer);
  return 0;
}
