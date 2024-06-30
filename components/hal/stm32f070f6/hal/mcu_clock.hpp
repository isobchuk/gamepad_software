#pragma once

#include "hal_clock.hpp"
#include "meta_types.hpp"
#include "reg_flash.hpp"
#include "reg_rcc.hpp"

namespace stm32f0x0::clock {

enum class SourceClockType : uint32_t { HSI = 0b00, HSE = 0b10, MASK = 0b11 };

template <const SourceClockType sourceClockType, const uint32_t frequency>
concept source_clock_frequency =
    ((SourceClockType::HSE == sourceClockType) ? ((4'000'000UL <= frequency) && (frequency <= 32'000'000UL)) : (8'000'000UL == frequency));

template <const uint32_t frequency>
concept system_frequency = (frequency <= 48'000'000UL);

template <const SourceClockType sourceClockType, const uint32_t frequency = 8'000'000UL>
requires source_clock_frequency<sourceClockType, frequency>
struct SourceClock {
  static constexpr auto sc_SourceClockType = sourceClockType;
  static constexpr auto sc_Frequency = frequency;
  struct SourceClockT;
};

using HSI = SourceClock<SourceClockType::HSI>;
template <const uint32_t frequency> using HSE = SourceClock<SourceClockType::HSE, frequency>;

template <typename T>
concept source_clock = requires(T) {
  T::sc_SourceClockType;
  T::sc_Frequency;
  typename T::SourceClockT;
};

template <source_clock SourceClock, const uint32_t systemFreq = SourceClock::sc_Frequency>
requires system_frequency<systemFreq>
class SystemClock final {
  static constexpr auto scSystemFrequency = systemFreq;
  static constexpr auto scSourceFrequency = SourceClock::sc_Frequency;
  static constexpr auto scSourceType = SourceClock::sc_SourceClockType;

public:
  inline consteval SystemClock() { static_assert(::hal::clock::system_clock<SystemClock>, "The class should implement a whole concept interface!"); }

  inline void Init(void) const {
    using namespace stm32f0x0::rcc;
    using namespace stm32f0x0::flash;
    using namespace cpp_register;
    using enum SourceClockType;

    // If HSE is a source - enable it
    if constexpr (SourceClockType::HSE == scSourceType) {
      RCC->CR |= RCC_CR::HSEON;
      while (!(RCC->CR & RCC_CR::HSERDY)) {
      }
    }

    // Check if PLL is needed
    constexpr bool isPllNeeded = (scSourceFrequency != scSystemFrequency);
    if constexpr (isPllNeeded) {
      // Calculate the divider and the multiplier
      constexpr float pllCoefficient = static_cast<float>(scSystemFrequency) / static_cast<float>(scSourceFrequency);
      constexpr float pllFraction =
          (static_cast<float>(static_cast<uint32_t>((pllCoefficient - static_cast<uint32_t>(pllCoefficient))) * 100) / 100.0f);
      constexpr uint32_t pllDivider = static_cast<uint32_t>(1.0f / ((pllFraction > 0) ? pllFraction : 1)) - 1;
      constexpr uint32_t pllMultiplier = scSystemFrequency / (scSourceFrequency / (pllDivider + 1)) - 2;
      static_assert((pllDivider < 16), "Ensure that PLL Divider can be calculated!");
      static_assert((pllMultiplier < 16), "Ensure that PLL Multiplier can be calculated!");

      // Set the latency if needed
      if constexpr (scSystemFrequency > 24'000'000UL) {
        FLASH->ACR |= FLASH_ACR::LATENCY(reg_v<1UL>) | FLASH_ACR::PRFTBE;
      }

      // Set clock configuration according to the source, multiplier and divider
      constexpr auto clockSourceRegister = scSourceType;
      if constexpr (pllDivider > 1U) {
        RCC->CFGR |= RCC_CFGR::PLLSRC(reg_v<clockSourceRegister>) | RCC_CFGR::PLLMUL(reg_v<pllMultiplier>);
        RCC->CFGR2 = RCC_CFGR2::PREDIV(reg_v<pllDivider>);
      } else {
        RCC->CFGR |= RCC_CFGR::PLLSRC(reg_v<clockSourceRegister>) | RCC_CFGR::PLLMUL(reg_v<pllMultiplier>) | RCC_CFGR::PLLXTPRE(reg_v<pllDivider>);
      }

      // Enable PLL
      RCC->CR |= RCC_CR::PLLON;
      while (!(RCC->CR & RCC_CR::PLLRDY)) {
      }

      // Set the PLL source
      RCC->CFGR |= RCC_CFGR::SW(reg_v<clockSourceRegister>);
      while (RCC_CFGR::SWS(reg_v<clockSourceRegister>) != (RCC->CFGR & RCC_CFGR::SWS(reg_v<MASK>))) {
      }
    }
  }

  [[nodiscard]] inline consteval unsigned long Frequency(void) const { return scSystemFrequency; }
};

} // namespace stm32f0x0::clock