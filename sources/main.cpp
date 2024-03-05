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

  RCC->AHBENR |= RCC_AHBENR::IOPAEN | RCC_AHBENR::IOPBEN;

  static constexpr gamepad::gpio::GpioController<gamepad::sc_Pin> gpio;
  gpio.Init();

  static constexpr auto SYSTEM_MHZ = 8UL;
  static constexpr auto SYST_PERIOD = reg_v<(SYSTEM_MHZ * 1000000UL) / 2 - 1>;

  STK->RVR = STK_RVR::RELOAD(SYST_PERIOD);
  STK->CVR = STK_CVR::CURRENT(SYST_PERIOD);
  STK->CSR |= (STK_CSR::CLKSOURCE | STK_CSR::ENABLE);

  while (true) {
    if (STK->CSR & STK_CSR::COUNTFLAG) {
      gpio[const_v<gamepad::PinFunction::Led>].Change();
    }
  }

  return 0;
}