#pragma once

#include "register.hpp"

namespace stm32f0x0::rcc {

template <const cpp_register::RegisterAddress address> struct RCC_T {
  static constexpr cpp_register::Register<address + 0x0, cpp_register::AccessMode::RW, uint32_t, struct CR> CR{};
  static constexpr cpp_register::Register<address + 0x4, cpp_register::AccessMode::RW, uint32_t, struct CFGR> CFGR{};
  static constexpr cpp_register::Register<address + 0x8, cpp_register::AccessMode::R, uint32_t, struct CIR> CIR{};
  static constexpr cpp_register::Register<address + 0xC, cpp_register::AccessMode::RW, uint32_t, struct APB2RSTR> APB2RSTR{};
  static constexpr cpp_register::Register<address + 0x10, cpp_register::AccessMode::RW, uint32_t, struct APB1RSTR> APB1RSTR{};
  static constexpr cpp_register::Register<address + 0x14, cpp_register::AccessMode::RW, uint32_t, struct AHBENR> AHBENR{};
  static constexpr cpp_register::Register<address + 0x18, cpp_register::AccessMode::RW, uint32_t, struct APB2ENR> APB2ENR{};
  static constexpr cpp_register::Register<address + 0x1C, cpp_register::AccessMode::RW, uint32_t, struct APB1ENR> APB1ENR{};
  static constexpr cpp_register::Register<address + 0x20, cpp_register::AccessMode::RW, uint32_t, struct BDCR> BDCR{};
  static constexpr cpp_register::Register<address + 0x24, cpp_register::AccessMode::RW, uint32_t, struct CSR> CSR{};
  static constexpr cpp_register::Register<address + 0x28, cpp_register::AccessMode::RW, uint32_t, struct AHBRSTR> AHBRSTR{};
  static constexpr cpp_register::Register<address + 0x2C, cpp_register::AccessMode::RW, uint32_t, struct CFGR2> CFGR2{};
  static constexpr cpp_register::Register<address + 0x30, cpp_register::AccessMode::RW, uint32_t, struct CFGR3> CFGR3{};
  static constexpr cpp_register::Register<address + 0x34, cpp_register::AccessMode::RW, uint32_t, struct CR2> CR2{};
};

inline constexpr RCC_T<0x40021000> const *RCC{};

struct RCC_CR {
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 0), cpp_register::AccessMode::RW, 1> HSION{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 1), cpp_register::AccessMode::RW, 1> HSIRDY{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 3), cpp_register::AccessMode::RW, 5> HSITRIM{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 8), cpp_register::AccessMode::RW, 8> HSICAL{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 16), cpp_register::AccessMode::RW, 1> HSEON{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 17), cpp_register::AccessMode::RW, 1> HSERDY{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 18), cpp_register::AccessMode::RW, 1> HSEBYP{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 19), cpp_register::AccessMode::RW, 1> CSSON{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 24), cpp_register::AccessMode::RW, 1> PLLON{};
  static constexpr cpp_register::Field<decltype(RCC->CR), (1UL << 25), cpp_register::AccessMode::RW, 1> PLLRDY{};
};

struct RCC_CFGR {
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 0), cpp_register::AccessMode::RW, 2> SW{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 2), cpp_register::AccessMode::RW, 2> SWS{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 4), cpp_register::AccessMode::RW, 4> HPRE{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 8), cpp_register::AccessMode::RW, 3> PPRE{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 14), cpp_register::AccessMode::RW, 1> ADCPRE{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 15), cpp_register::AccessMode::RW, 2> PLLSRC{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 17), cpp_register::AccessMode::RW, 1> PLLXTPRE{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 18), cpp_register::AccessMode::RW, 4> PLLMUL{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 24), cpp_register::AccessMode::RW, 3> MCO{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 28), cpp_register::AccessMode::RW, 3> MCOPRE{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR), (1UL << 31), cpp_register::AccessMode::RW, 1> PLLNODIV{};
};

struct RCC_CIR {
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 0), cpp_register::AccessMode::R, 1> LSIRDYF{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 1), cpp_register::AccessMode::R, 1> LSERDYF{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 2), cpp_register::AccessMode::R, 1> HSIRDYF{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 3), cpp_register::AccessMode::R, 1> HSERDYF{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 4), cpp_register::AccessMode::R, 1> PLLRDYF{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 5), cpp_register::AccessMode::R, 1> HSI14RDYF{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 6), cpp_register::AccessMode::R, 1> HSI48RDYF{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 7), cpp_register::AccessMode::R, 1> CSSF{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 8), cpp_register::AccessMode::R, 1> LSIRDYIE{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 9), cpp_register::AccessMode::R, 1> LSERDYIE{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 10), cpp_register::AccessMode::R, 1> HSIRDYIE{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 11), cpp_register::AccessMode::R, 1> HSERDYIE{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 12), cpp_register::AccessMode::R, 1> PLLRDYIE{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 13), cpp_register::AccessMode::R, 1> HSI14RDYE{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 14), cpp_register::AccessMode::R, 1> HSI48RDYIE{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 16), cpp_register::AccessMode::R, 1> LSIRDYC{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 17), cpp_register::AccessMode::R, 1> LSERDYC{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 18), cpp_register::AccessMode::R, 1> HSIRDYC{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 19), cpp_register::AccessMode::R, 1> HSERDYC{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 20), cpp_register::AccessMode::R, 1> PLLRDYC{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 21), cpp_register::AccessMode::R, 1> HSI14RDYC{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 22), cpp_register::AccessMode::R, 1> HSI48RDYC{};
  static constexpr cpp_register::Field<decltype(RCC->CIR), (1UL << 23), cpp_register::AccessMode::R, 1> CSSC{};
};

struct RCC_APB2RSTR {
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 0), cpp_register::AccessMode::RW, 1> SYSCFGRST{};
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 9), cpp_register::AccessMode::RW, 1> ADCRST{};
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 11), cpp_register::AccessMode::RW, 1> TIM1RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 12), cpp_register::AccessMode::RW, 1> SPI1RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 14), cpp_register::AccessMode::RW, 1> USART1RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 16), cpp_register::AccessMode::RW, 1> TIM15RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 17), cpp_register::AccessMode::RW, 1> TIM16RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 18), cpp_register::AccessMode::RW, 1> TIM17RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB2RSTR), (1UL << 22), cpp_register::AccessMode::RW, 1> DBGMCURST{};
};

struct RCC_APB1RSTR {
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 1), cpp_register::AccessMode::RW, 1> TIM3RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 4), cpp_register::AccessMode::RW, 1> TIM6RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 5), cpp_register::AccessMode::RW, 1> TIM7RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 8), cpp_register::AccessMode::RW, 1> TIM14RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 11), cpp_register::AccessMode::RW, 1> WWDGRST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 14), cpp_register::AccessMode::RW, 1> SPI2RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 17), cpp_register::AccessMode::RW, 1> USART2RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 18), cpp_register::AccessMode::RW, 1> USART3RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 19), cpp_register::AccessMode::RW, 1> USART4RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 20), cpp_register::AccessMode::RW, 1> USART5RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 21), cpp_register::AccessMode::RW, 1> I2C1RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 22), cpp_register::AccessMode::RW, 1> I2C2RST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 23), cpp_register::AccessMode::RW, 1> USBRST{};
  static constexpr cpp_register::Field<decltype(RCC->APB1RSTR), (1UL << 28), cpp_register::AccessMode::RW, 1> PWRRST{};
};

struct RCC_AHBENR {
  static constexpr cpp_register::Field<decltype(RCC->AHBENR), (1UL << 0), cpp_register::AccessMode::RW, 1> DMA1EN{};
  static constexpr cpp_register::Field<decltype(RCC->AHBENR), (1UL << 2), cpp_register::AccessMode::RW, 1> SRAMEN{};
  static constexpr cpp_register::Field<decltype(RCC->AHBENR), (1UL << 4), cpp_register::AccessMode::RW, 1> FLITFEN{};
  static constexpr cpp_register::Field<decltype(RCC->AHBENR), (1UL << 6), cpp_register::AccessMode::RW, 1> CRCEN{};
  static constexpr cpp_register::Field<decltype(RCC->AHBENR), (1UL << 17), cpp_register::AccessMode::RW, 1> IOPAEN{};
  static constexpr cpp_register::Field<decltype(RCC->AHBENR), (1UL << 18), cpp_register::AccessMode::RW, 1> IOPBEN{};
  static constexpr cpp_register::Field<decltype(RCC->AHBENR), (1UL << 19), cpp_register::AccessMode::RW, 1> IOPCEN{};
  static constexpr cpp_register::Field<decltype(RCC->AHBENR), (1UL << 22), cpp_register::AccessMode::RW, 1> IOPFEN{};
};

struct RCC_APB2ENR {
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 0), cpp_register::AccessMode::RW, 1> SYSCFGEN{};
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 9), cpp_register::AccessMode::RW, 1> ADCEN{};
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 11), cpp_register::AccessMode::RW, 1> TIM1EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 12), cpp_register::AccessMode::RW, 1> SPI1EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 14), cpp_register::AccessMode::RW, 1> USART1EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 16), cpp_register::AccessMode::RW, 1> TIM15EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 17), cpp_register::AccessMode::RW, 1> TIM16EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 18), cpp_register::AccessMode::RW, 1> TIM17EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB2ENR), (1UL << 22), cpp_register::AccessMode::RW, 1> DBGMCUEN{};
};

struct RCC_APB1ENR {
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 1), cpp_register::AccessMode::RW, 1> TIM3EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 4), cpp_register::AccessMode::RW, 1> TIM6EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 5), cpp_register::AccessMode::RW, 1> TIM7EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 8), cpp_register::AccessMode::RW, 1> TIM14EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 11), cpp_register::AccessMode::RW, 1> WWDGEN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 14), cpp_register::AccessMode::RW, 1> SPI2EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 17), cpp_register::AccessMode::RW, 1> USART2EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 18), cpp_register::AccessMode::RW, 1> USART3EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 19), cpp_register::AccessMode::RW, 1> USART4EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 20), cpp_register::AccessMode::RW, 1> USART5EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 21), cpp_register::AccessMode::RW, 1> I2C1EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 22), cpp_register::AccessMode::RW, 1> I2C2EN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 23), cpp_register::AccessMode::RW, 1> USBEN{};
  static constexpr cpp_register::Field<decltype(RCC->APB1ENR), (1UL << 28), cpp_register::AccessMode::RW, 1> PWREN{};
};

struct RCC_BDCR {
  static constexpr cpp_register::Field<decltype(RCC->BDCR), (1UL << 0), cpp_register::AccessMode::RW, 1> LSEON{};
  static constexpr cpp_register::Field<decltype(RCC->BDCR), (1UL << 1), cpp_register::AccessMode::RW, 1> LSERDY{};
  static constexpr cpp_register::Field<decltype(RCC->BDCR), (1UL << 2), cpp_register::AccessMode::RW, 1> LSEBYP{};
  static constexpr cpp_register::Field<decltype(RCC->BDCR), (1UL << 3), cpp_register::AccessMode::RW, 2> LSEDRV{};
  static constexpr cpp_register::Field<decltype(RCC->BDCR), (1UL << 8), cpp_register::AccessMode::RW, 2> RTCSEL{};
  static constexpr cpp_register::Field<decltype(RCC->BDCR), (1UL << 15), cpp_register::AccessMode::RW, 1> RTCEN{};
  static constexpr cpp_register::Field<decltype(RCC->BDCR), (1UL << 16), cpp_register::AccessMode::RW, 1> BDRST{};
};

struct RCC_CSR {
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 0), cpp_register::AccessMode::RW, 1> LSION{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 1), cpp_register::AccessMode::RW, 1> LSIRDY{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 24), cpp_register::AccessMode::RW, 1> RMVF{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 25), cpp_register::AccessMode::RW, 1> OBLRSTF{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 26), cpp_register::AccessMode::RW, 1> PINRSTF{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 27), cpp_register::AccessMode::RW, 1> PORRSTF{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 28), cpp_register::AccessMode::RW, 1> SFTRSTF{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 29), cpp_register::AccessMode::RW, 1> IWDGRSTF{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 30), cpp_register::AccessMode::RW, 1> WWDGRSTF{};
  static constexpr cpp_register::Field<decltype(RCC->CSR), (1UL << 31), cpp_register::AccessMode::RW, 1> LPWRRSTF{};
};

struct RCC_AHBRSTR {
  static constexpr cpp_register::Field<decltype(RCC->AHBRSTR), (1UL << 17), cpp_register::AccessMode::RW, 1> IOPARST{};
  static constexpr cpp_register::Field<decltype(RCC->AHBRSTR), (1UL << 18), cpp_register::AccessMode::RW, 1> IOPBRST{};
  static constexpr cpp_register::Field<decltype(RCC->AHBRSTR), (1UL << 19), cpp_register::AccessMode::RW, 1> IOPCRST{};
  static constexpr cpp_register::Field<decltype(RCC->AHBRSTR), (1UL << 20), cpp_register::AccessMode::RW, 1> IOPDRST{};
  static constexpr cpp_register::Field<decltype(RCC->AHBRSTR), (1UL << 22), cpp_register::AccessMode::RW, 1> IOPFRST{};
};

struct RCC_CFGR2 {
  static constexpr cpp_register::Field<decltype(RCC->CFGR2), (1UL << 0), cpp_register::AccessMode::RW, 4> PREDIV{};
};

struct RCC_CFGR3 {
  static constexpr cpp_register::Field<decltype(RCC->CFGR3), (1UL << 0), cpp_register::AccessMode::RW, 2> USART1SW{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR3), (1UL << 4), cpp_register::AccessMode::RW, 1> I2C1SW{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR3), (1UL << 6), cpp_register::AccessMode::RW, 1> CECSW{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR3), (1UL << 7), cpp_register::AccessMode::RW, 1> USBSW{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR3), (1UL << 8), cpp_register::AccessMode::RW, 1> ADCSW{};
  static constexpr cpp_register::Field<decltype(RCC->CFGR3), (1UL << 16), cpp_register::AccessMode::RW, 2> USART2SW{};
};

struct RCC_CR2 {
  static constexpr cpp_register::Field<decltype(RCC->CR2), (1UL << 0), cpp_register::AccessMode::RW, 1> HSI14ON{};
  static constexpr cpp_register::Field<decltype(RCC->CR2), (1UL << 1), cpp_register::AccessMode::RW, 1> HSI14RDY{};
  static constexpr cpp_register::Field<decltype(RCC->CR2), (1UL << 2), cpp_register::AccessMode::RW, 1> HSI14DIS{};
  static constexpr cpp_register::Field<decltype(RCC->CR2), (1UL << 3), cpp_register::AccessMode::RW, 5> HSI14TRIM{};
  static constexpr cpp_register::Field<decltype(RCC->CR2), (1UL << 8), cpp_register::AccessMode::RW, 8> HSI14CAL{};
  static constexpr cpp_register::Field<decltype(RCC->CR2), (1UL << 16), cpp_register::AccessMode::RW, 1> HSI48ON{};
  static constexpr cpp_register::Field<decltype(RCC->CR2), (1UL << 17), cpp_register::AccessMode::RW, 1> HSI48RDY{};
  static constexpr cpp_register::Field<decltype(RCC->CR2), (1UL << 24), cpp_register::AccessMode::RW, 1> HSI48CAL{};
};

} // namespace stm32f0x0::rcc
