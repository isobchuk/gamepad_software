#pragma once

#include "meta_types.hpp"
#include "reg_rcc.hpp"

template <typename SystemClockT>
concept hal_system_clock = requires(SystemClockT) { SystemClockT::Frequency; };

namespace stm32f0x0::hal::clock {

enum class SourceType { HSI, HSE };

template <const SourceType sourceType, const uint32_t frequency = 8'000'000UL> struct SourceClock {
  static constexpr auto sc_SourceType = sourceType;
  static constexpr auto sc_Frequency = frequency;
  struct SourceClockT;
};

using HSI = SourceClock<SourceType::HSI>;
template <const uint32_t frequency> using HSE = SourceClock<SourceType::HSE, frequency>;

template <typename T>
concept source_clock = requires(T) {
  T::sc_SourceType;
  T::sc_Frequency;
  typename T::SourceClockT;
};

template <source_clock SourceClock, const uint32_t systemFreq> class SystemClock final {

  static constexpr auto Frequency = systemFreq;

public:
  consteval SystemClock() { static_assert(hal_system_clock<SystemClock>, "The class should implement a whole concept interface!"); }

  inline void Init(void) {}
};

} // namespace stm32f0x0::hal::clock