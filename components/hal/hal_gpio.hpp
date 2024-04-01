#pragma once

#include "meta_types.hpp"
#include <concepts>

namespace hal::gpio {
template <typename GpioT>
concept gpio_out = requires(const GpioT gp) {
  { gp.Write(iso::meta_type::const_v<bool{}>) } -> std::same_as<void>;
  { gp.Change() } -> std::same_as<void>;
  typename GpioT::PinType;
};

template <typename GpioT>
concept gpio_in = requires(const GpioT gp) {
  { gp.Read() } -> std::same_as<bool>;
  typename GpioT::PinType;
};

template <typename GpioT>
concept is_gpio = requires(const GpioT) { typename GpioT::PinType; };

template <typename GpioControllerT>
concept gpio_controller = requires(const GpioControllerT gpControl) {
  typename GpioControllerT::PinFunction;
  { gpControl.Init() } -> std::same_as<void>;
  { gpControl[iso::meta_type::const_v<typename GpioControllerT::PinFunction{}>] } -> is_gpio;
};
} // namespace hal::gpio