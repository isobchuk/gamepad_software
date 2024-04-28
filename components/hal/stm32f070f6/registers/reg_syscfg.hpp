#pragma once

#include "register.hpp"

namespace stm32f0x0::syscfg {

template <const cpp_register::RegisterAddress address> struct SYSCFG_T {
  static constexpr cpp_register::Register<address + 0x0, cpp_register::AccessMode::RW, uint32_t, struct CFGR1> CFGR1{};
  static constexpr cpp_register::Register<address + 0x8, cpp_register::AccessMode::RW, uint32_t, struct EXTICR, 4> EXTICR{};
  static constexpr cpp_register::Register<address + 0x18, cpp_register::AccessMode::RW, uint32_t, struct CFGR2> CFGR2{};
};

inline constexpr SYSCFG_T<0x40010000> const *SYSCFG{};

struct SYSCFG_CFGR1 {
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 0), cpp_register::AccessMode::RW, 2> MEM_MODE{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 4), cpp_register::AccessMode::RW, 1> PA11_PA12_RMP{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 8), cpp_register::AccessMode::RW, 1> ADC_DMA_RMP{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 9), cpp_register::AccessMode::RW, 1> USART1_TX_DMA_RMP{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 10), cpp_register::AccessMode::RW, 1> USART1_RX_DMA_RMP{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 11), cpp_register::AccessMode::RW, 1> TIM16_DMA_RMP{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 12), cpp_register::AccessMode::RW, 1> TIM17_DMA_RMP{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 16), cpp_register::AccessMode::RW, 1> I2C_PB6_FM{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 17), cpp_register::AccessMode::RW, 1> I2C_PB7_FM{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 18), cpp_register::AccessMode::RW, 1> I2C_PB8_FM{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 19), cpp_register::AccessMode::RW, 1> I2C_PB9_FM{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 20), cpp_register::AccessMode::RW, 1> I2C1_FM_plus{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 21), cpp_register::AccessMode::RW, 1> I2C2_FM_plus{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 22), cpp_register::AccessMode::RW, 1> I2C_PA9_FM{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 23), cpp_register::AccessMode::RW, 1> I2C_PA10_FM{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR1), (1UL << 26), cpp_register::AccessMode::RW, 1> USART3_DMA_RMP{};
};

struct SYSCFG_EXTICR {
  static constexpr cpp_register::Field<decltype(SYSCFG->EXTICR), (1UL << 0), cpp_register::AccessMode::RW, 4, 4> EXTI{};
};

struct SYSCFG_CFGR2 {
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR2), (1UL << 8), cpp_register::AccessMode::RC_W1, 1> SRAM_PEF{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR2), (1UL << 1), cpp_register::AccessMode::RW, 1> SRAM_PARITY_LOCK{};
  static constexpr cpp_register::Field<decltype(SYSCFG->CFGR2), (1UL << 0), cpp_register::AccessMode::RW, 1> LOCUP_LOCK{};
};

} // namespace stm32f0x0::syscfg
