#pragma once

#include "hal_gpio.hpp"

namespace gamepad {

namespace mcu = stm32f0x0;
namespace gpio = mcu::hal::gpio;

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
} // namespace gamepad