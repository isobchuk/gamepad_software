#pragma once

#include "register.hpp"

namespace stm32f0x0::adc {

template <const cpp_register::RegisterAddress address> struct ADC_T {
  static constexpr cpp_register::Register<address + 0x0, cpp_register::AccessMode::RC_W1, uint32_t, struct ISR> ISR{};
  static constexpr cpp_register::Register<address + 0x4, cpp_register::AccessMode::RW, uint32_t, struct IER> IER{};
  static constexpr cpp_register::Register<address + 0x8, cpp_register::AccessMode::RS, uint32_t, struct CR> CR{};
  static constexpr cpp_register::Register<address + 0xC, cpp_register::AccessMode::RW, uint32_t, struct CFGR1> CFGR1{};
  static constexpr cpp_register::Register<address + 0x10, cpp_register::AccessMode::RW, uint32_t, struct CFGR2> CFGR2{};
  static constexpr cpp_register::Register<address + 0x14, cpp_register::AccessMode::RW, uint32_t, struct SMPR> SMPR{};
  static constexpr cpp_register::Register<address + 0x20, cpp_register::AccessMode::RW, uint32_t, struct TR> TR{};
  static constexpr cpp_register::Register<address + 0x28, cpp_register::AccessMode::RW, uint32_t, struct CHSELR> CHSELR{};
  static constexpr cpp_register::Register<address + 0x40, cpp_register::AccessMode::R, uint32_t, struct DR> DR{};
  static constexpr cpp_register::Register<address + 0x308, cpp_register::AccessMode::RW, uint32_t, struct CCR> CCR{};
};

inline constexpr ADC_T<0x40012400> const *ADC{};

struct ADC_ISR {
  static constexpr cpp_register::Field<decltype(ADC->ISR), (1UL << 7), cpp_register::AccessMode::RC_W1, 1> AWD{};
  static constexpr cpp_register::Field<decltype(ADC->ISR), (1UL << 4), cpp_register::AccessMode::RC_W1, 1> OVR{};
  static constexpr cpp_register::Field<decltype(ADC->ISR), (1UL << 3), cpp_register::AccessMode::RC_W1, 1> EOS{};
  static constexpr cpp_register::Field<decltype(ADC->ISR), (1UL << 2), cpp_register::AccessMode::RC_W1, 1> EOC{};
  static constexpr cpp_register::Field<decltype(ADC->ISR), (1UL << 1), cpp_register::AccessMode::RC_W1, 1> EOSMP{};
  static constexpr cpp_register::Field<decltype(ADC->ISR), (1UL << 0), cpp_register::AccessMode::RC_W1, 1> ADRDY{};
};

struct ADC_IER {
  static constexpr cpp_register::Field<decltype(ADC->IER), (1UL << 7), cpp_register::AccessMode::RW, 1> AWDIE{};
  static constexpr cpp_register::Field<decltype(ADC->IER), (1UL << 4), cpp_register::AccessMode::RW, 1> OVRIE{};
  static constexpr cpp_register::Field<decltype(ADC->IER), (1UL << 3), cpp_register::AccessMode::RW, 1> EOSIE{};
  static constexpr cpp_register::Field<decltype(ADC->IER), (1UL << 2), cpp_register::AccessMode::RW, 1> EOCIE{};
  static constexpr cpp_register::Field<decltype(ADC->IER), (1UL << 1), cpp_register::AccessMode::RW, 1> EOSMPIE{};
  static constexpr cpp_register::Field<decltype(ADC->IER), (1UL << 0), cpp_register::AccessMode::RW, 1> ADRDYIE{};
};

struct ADC_CR {
  static constexpr cpp_register::Field<decltype(ADC->CR), (1UL << 31), cpp_register::AccessMode::RS, 1> ADCAL{};
  static constexpr cpp_register::Field<decltype(ADC->CR), (1UL << 4), cpp_register::AccessMode::RS, 1> ADSTP{};
  static constexpr cpp_register::Field<decltype(ADC->CR), (1UL << 2), cpp_register::AccessMode::RS, 1> ADSTART{};
  static constexpr cpp_register::Field<decltype(ADC->CR), (1UL << 1), cpp_register::AccessMode::RS, 1> ADDIS{};
  static constexpr cpp_register::Field<decltype(ADC->CR), (1UL << 0), cpp_register::AccessMode::RS, 1> ADEN{};
};

struct ADC_CFGR1 {
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 26), cpp_register::AccessMode::RW, 5> AWDCH{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 23), cpp_register::AccessMode::RW, 1> AWDEN{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 22), cpp_register::AccessMode::RW, 1> AWDSGL{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 16), cpp_register::AccessMode::RW, 1> DISCEN{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 15), cpp_register::AccessMode::RW, 1> AUTOFF{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 14), cpp_register::AccessMode::RW, 1> AUTDLY{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 13), cpp_register::AccessMode::RW, 1> CONT{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 12), cpp_register::AccessMode::RW, 1> OVRMOD{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 10), cpp_register::AccessMode::RW, 2> EXTEN{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 6), cpp_register::AccessMode::RW, 3> EXTSEL{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 5), cpp_register::AccessMode::RW, 1> ALIGN{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 3), cpp_register::AccessMode::RW, 2> RES{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 2), cpp_register::AccessMode::RW, 1> SCANDIR{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 1), cpp_register::AccessMode::RW, 1> DMACFG{};
  static constexpr cpp_register::Field<decltype(ADC->CFGR1), (1UL << 0), cpp_register::AccessMode::RW, 1> DMAEN{};
};

struct ADC_CFGR2 {
  static constexpr cpp_register::Field<decltype(ADC->CFGR2), (1UL << 27), cpp_register::AccessMode::RW, 1, 5> JITOFF_D{};
};

struct ADC_SMPR {
  static constexpr cpp_register::Field<decltype(ADC->SMPR), (1UL << 0), cpp_register::AccessMode::RW, 3> SMPR{};
};

struct ADC_TR {
  static constexpr cpp_register::Field<decltype(ADC->TR), (1UL << 16), cpp_register::AccessMode::RW, 12> HT{};
  static constexpr cpp_register::Field<decltype(ADC->TR), (1UL << 0), cpp_register::AccessMode::RW, 12> LT{};
};

struct ADC_CHSELR {
  static constexpr cpp_register::Field<decltype(ADC->CHSELR), (1UL << 0), cpp_register::AccessMode::RW, 1, 19> CHSEL{};
};

struct ADC_DR {
  static constexpr cpp_register::Field<decltype(ADC->DR), (1UL << 0), cpp_register::AccessMode::R, 16> DATA{};
};

struct ADC_CCR {
  static constexpr cpp_register::Field<decltype(ADC->CCR), (1UL << 24), cpp_register::AccessMode::RW, 1> VBATEN{};
  static constexpr cpp_register::Field<decltype(ADC->CCR), (1UL << 23), cpp_register::AccessMode::RW, 1> TSEN{};
  static constexpr cpp_register::Field<decltype(ADC->CCR), (1UL << 22), cpp_register::AccessMode::RW, 1> VREFEN{};
};

} // namespace stm32f0x0::adc
