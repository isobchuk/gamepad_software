#include "reg_gpio.hpp"
#include "reg_rcc.hpp"
#include "reg_stk.hpp"

#include "config.hpp"
#include "hal_gpio.hpp"
#include "hal_interrupts.hpp"
#include "meta_types.hpp"

#include "hal_clock.hpp"

using namespace cpp_register;
using namespace cpp_register::constants;
using namespace stm32f0x0::stk;
using namespace stm32f0x0::gpio;
using namespace stm32f0x0::rcc;

using namespace iso::meta_type;

static constexpr stm32f0x0::hal::clock::SystemClock<stm32f0x0::hal::clock::HSE<gamepad::sc_QuartzClock>, gamepad::sc_SystemClock> clock{};

int main() {
  clock.Init();
  RCC->AHBENR |= RCC_AHBENR::IOPAEN | RCC_AHBENR::IOPBEN;

  static constexpr gamepad::gpio::GpioController<gamepad::sc_Pin> gpio;
  gpio.Init();

  static constexpr auto SYST_PERIOD = reg_v<(gamepad::sc_SystemClock / 1000) - 1>;

  STK->RVR = STK_RVR::RELOAD(SYST_PERIOD);
  STK->CVR = STK_CVR::CURRENT(SYST_PERIOD);
  STK->CSR |= (STK_CSR::CLKSOURCE | STK_CSR::ENABLE);

  uint32_t time = 0;
  while (true) {
    if (STK->CSR & STK_CSR::COUNTFLAG) {
      time++;
    }
    if (1000 == time) {
      time = 0;
      gpio[const_v<gamepad::PinFunction::Led>].Change();
    }
  }

  return 0;
}