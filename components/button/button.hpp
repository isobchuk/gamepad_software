#pragma once

#include "hal_gpio.hpp"
#include "meta_types.hpp"
#include <concepts>

namespace hardware::button {

template <::hal::gpio::gpio_in Pin, iso::meta_type::const_value_of_type<bool> Negative> class Button final {
  const Pin mPin;
  static constexpr bool mIsNegativeActive = Negative::value;

public:
  consteval Button(const Pin pin, const Negative) : mPin(pin) {}

  inline bool Read() const {
    if constexpr (mIsNegativeActive) {
      return !mPin.Read();
    } else {
      return mPin.Read();
    }
  }
};

} // namespace hardware::button