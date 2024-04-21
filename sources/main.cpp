#include "config.hpp"

using namespace gamepad;

int main() {
  processor::interrupt.GlobalEnable();
  processor::clock.Init();
  processor::gpio.Init();
  processor::systemTimer.Init();

  Timeout timeoutLed;

  while (true) {
    time.Start(timeoutLed);
    if (time.Check(timeoutLed, 250U)) {
      led.Change();
    }
  }

  return 0;
}