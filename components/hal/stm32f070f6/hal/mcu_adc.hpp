#pragma once

#include "meta_types.hpp"
#include "reg_adc.hpp"
#include "reg_rcc.hpp"

namespace stm32f0x0::adc {

enum class EAdcChannels : uint32_t {
  Number0 = 1U << 0,
  Number1 = 1U << 1,
  Number2 = 1U << 2,
  Number3 = 1U << 3,
  Number4 = 1U << 4,
  Number5 = 1U << 5,
  Number6 = 1U << 6,
  Number7 = 1U << 7,
  Number8 = 1U << 8,
  Number9 = 1U << 9,
  Number10 = 1U << 10,
  Number11 = 1U << 11,
  Number12 = 1U << 12,
  Number13 = 1U << 13,
  Number14 = 1U << 14,
  Number15 = 1U << 15,
  Number16 = 1U << 16,
  Number17 = 1U << 17,

};

template <iso::meta_type::const_value_of_type<EAdcChannels>... Channels> class CAdc final {
  static constexpr auto _VREF = 3'300U;
  static constexpr uint32_t _ChannelsTable[] = {static_cast<uint32_t>(Channels::value)...};

public:
  consteval CAdc(const Channels...) {}

  inline void Init() const {
    using namespace cpp_register;
    using namespace stm32f0x0::rcc;

    // Enable ADC clock
    RCC->APB2ENR |= RCC_APB2ENR::ADCEN;

    // Set channels
    ADC->CHSELR = ADC_CHSELR::CHSEL[reg_v<(static_cast<uint32_t>(Channels::value) | ...)>];

    // Continuous conversion mode
    ADC->CFGR1 |= ADC_CFGR1::CONT;

    // Enable ADC
    ADC->CFGR1 |= ADC_CFGR1::RES(reg_v<0b10U>);
    ADC->CR |= ADC_CR::ADEN;
  }

  template <typename T> inline void Value(T (&buffer)[sizeof...(Channels)]) const {
    ADC->CR |= ADC_CR::ADSTART;

    for (auto &ch : buffer) {
      while (!(ADC->ISR & ADC_ISR::EOC)) {
      }
      ADC->ISR |= ADC_ISR::EOC;
      ch = static_cast<T>(*(ADC->DR) /* >> (12 - (8 * sizeof(T)))*/);
    }
    while (!(ADC->ISR & ADC_ISR::EOS)) {
    }
    ADC->ISR |= ADC_ISR::EOS;
    ADC->CR |= ADC_CR::ADSTP;
  }
};
} // namespace stm32f0x0::adc