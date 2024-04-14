#include "config.hpp"

static volatile uint32_t time;

// static constexpr system_time::SystemTime systemTime(time);

using namespace gamepad;

int main() {
  processor::interrupt.GlobalEnable();
  processor::clock.Init();
  processor::gpio.Init();
  processor::systemTimer.Init();

  while (true) {
  }

  return 0;
}

void SysTick_Handler(void) {
  time = time + 1;
  if (!(time % 1000)) {
    led.Change();
  }
}