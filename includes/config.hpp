#pragma once

#include "mcu_clock.hpp"
#include "mcu_gpio.hpp"
#include "mcu_interrupts.hpp"
#include "mcu_systick.hpp"
#include "mcu_usb.hpp"

#include "led.hpp"
#include "meta_types.hpp"
#include "system_time.hpp"

namespace gamepad {

namespace mcu = stm32f0x0;
namespace gpio = mcu::gpio;

enum class PinFunction : unsigned {
  JoystickAxisX,
  JoystickAxisY,
  JoystickButton,
  ButtonLed,
  ButtonX,
  ButtonY,
  ButtonA,
  ButtonB,
  UsbDn,
  UsbDp,
  Led,
  Num
};

// clang-format off
inline constexpr gpio::PinOut<PinFunction> sc_Pin[] = {
    // Joystick
    {PinFunction::JoystickAxisX,  gpio::Port::PA,   gpio::Pin::Pin_0,   gpio::Mode::Analog,     {}},
    {PinFunction::JoystickAxisY,  gpio::Port::PA,   gpio::Pin::Pin_1,   gpio::Mode::Analog,     {}},
    {PinFunction::JoystickButton, gpio::Port::PA,   gpio::Pin::Pin_2,   gpio::Mode::Input,      {}},

    // Buttons
    {PinFunction::ButtonLed,      gpio::Port::PA,   gpio::Pin::Pin_3,   gpio::Mode::Input,      {}},
    {PinFunction::ButtonX,        gpio::Port::PA,   gpio::Pin::Pin_4,   gpio::Mode::Input,      {}},
    {PinFunction::ButtonY,        gpio::Port::PA,   gpio::Pin::Pin_5,   gpio::Mode::Input,      {}},
    {PinFunction::ButtonA,        gpio::Port::PA,   gpio::Pin::Pin_6,   gpio::Mode::Input,      {}},
    {PinFunction::ButtonB,        gpio::Port::PA,   gpio::Pin::Pin_7,   gpio::Mode::Input,      {}},

    // USB
    {PinFunction::UsbDn,          gpio::Port::PA,   gpio::Pin::Pin_11,  gpio::Mode::Alternate,  {gpio::Speed::High, gpio::Alternative::AF7}},
    {PinFunction::UsbDp,          gpio::Port::PA,   gpio::Pin::Pin_12,  gpio::Mode::Alternate,  {gpio::Speed::High, gpio::Alternative::AF7}},

    // LED
    {PinFunction::Led,            gpio::Port::PB,   gpio::Pin::Pin_1,   gpio::Mode::Output,     {}}};
// clang-format on

static_assert((static_cast<std::underlying_type_t<PinFunction>>(PinFunction::Num) == (sizeof(sc_Pin) / sizeof(sc_Pin[0]))),
              "Ensure that all pins were configured!");

inline constexpr auto sc_QuartzClock = 8'000'000UL;
inline constexpr auto sc_SystemClock = 48'000'000UL;
using SystemTick = uint64_t;

struct processor {
  static constexpr mcu::clock::SystemClock<gamepad::mcu::clock::HSE<gamepad::sc_QuartzClock>, gamepad::sc_SystemClock> clock{};
  static constexpr gpio::GpioController<gamepad::sc_Pin> gpio{};
  static constexpr mcu::interrupt::InterruptController interrupt{};
  static constexpr mcu::system_timer::SystemTimer<gamepad::sc_SystemClock, mcu::system_timer::Unit::mS, SystemTick> systemTimer{};
  static constexpr mcu::usb::Usb usb{};
};

static constexpr hardware::led::Led led(processor::gpio[iso::meta_type::const_v<gamepad::PinFunction::Led>]);

static constexpr system_time::SystemTime time(processor::systemTimer);
using Timeout = decltype(time)::TimeoutTimer;

} // namespace gamepad