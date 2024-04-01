#include "config.hpp"

#include "mcu_clock.hpp"
#include "mcu_gpio.hpp"
#include "mcu_interrupts.hpp"
#include "mcu_systick.hpp"

#include "meta_types.hpp"

static constexpr gamepad::mcu::clock::SystemClock<gamepad::mcu::clock::HSE<gamepad::sc_QuartzClock>, gamepad::sc_SystemClock> clock{};
static constexpr gamepad::gpio::GpioController<gamepad::sc_Pin> gpio;
static constexpr gamepad::mcu::interrupt::InterruptController interrupt;
static constexpr gamepad::mcu::system_timer::SystemTimer<(gamepad::sc_SystemClock / 1000) - 1, true> systemTimer;

static volatile uint32_t time;

int main() {
  interrupt.GlobalEnable();
  clock.Init();
  gpio.Init();
  systemTimer.Init();

  while (true) {
  }

  return 0;
}

void SysTick_Handler(void) {
  time = time + 1;
  if (!(time % 1000)) {
    gpio[iso::meta_type::const_v<gamepad::PinFunction::Led>].Change();
  }
}