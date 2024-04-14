#pragma once

#include "hal_gpio.hpp"
#include "meta_types.hpp"

namespace hardware::led {

template <::hal::gpio::gpio_out Pin, const bool negative = false> class Led final {
  const Pin mPin;
  static constexpr bool mIsNegativeActive = negative;

public:
  consteval Led(const Pin pin) : mPin(pin) {}

  inline void Enable() const {
    if constexpr (mIsNegativeActive) {
      mPin.Write(iso::meta_type::const_v<false>);
    } else {
      mPin.Write(iso::meta_type::const_v<true>);
    }
  }

  inline void Disable() const {
    if constexpr (mIsNegativeActive) {
      mPin.Write(iso::meta_type::const_v<true>);
    } else {
      mPin.Write(iso::meta_type::const_v<false>);
    }
  }

  inline void Change() const { mPin.Change(); }
};

} // namespace hardware::led