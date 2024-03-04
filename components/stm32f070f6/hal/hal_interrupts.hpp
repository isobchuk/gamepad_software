#pragma once

#include "reg_nvic.hpp"
#include <concepts>

namespace stm32f0x0::hal::interrupt {

using InterruptT = uint32_t;

enum class Number : InterruptT {
  WWDG = 0,                 // Window Watchdog interrupt
  PVD = 1,                  // PVD and VDDIO2 supply comparator  interrupt
  RTC = 2,                  // RTC interrupts
  FLASH = 3,                // Flash global interrupt
  RCC = 4,                  // RCC global interruptr
  EXTI0_1 = 5,              // EXTI Line[1:0] interrupts
  EXTI2_3 = 6,              // EXTI Line[3:2] interrupts
  EXTI4_15 = 7,             // EXTI Line15 and EXTI4 interrupts
  DMA1_CH1 = 9,             // DMA1 channel 1 interrupt
  DMA1_CH2_3 = 10,          // DMA1 channel 2 and 3 interrupt
  DMA1_CH4_5 = 11,          // DMA1 channel 4 and 5 interrupt
  ADC = 12,                 // ADC interrupt
  TIM1_BRK_UP_TRG_COM = 13, // TIM1 break, update, trigger and commutation  interrupt
  TIM1_CC = 14,             // TIM1 Capture Compare interrupt
  TIM3 = 16,                // TIM3 global interrupt
  TIM6 = 17,                // TIM6 global interrupt
  TIM14 = 19,               // TIM14 global interrupt
  TIM15 = 20,               // TIM15 global interrupt
  TIM16 = 21,               // TIM16 global interrupt
  TIM17 = 22,               // TIM17 global interrupt
  I2C1 = 23,                // I2C1 global interrupt
  I2C2 = 24,                // I2C2 global interrupt
  SPI1 = 25,                // SPI1_global_interrupt
  SPI2 = 26,                // SPI2 global interrupt
  USART1 = 27,              // USART1 global interrupt
  USART2 = 28,              // USART2 global interrupt
  USART3_4_5_6 = 29,        // USART3, USART4, USART5, USART6 global  interrupt
  USB = 31,                 // USB global interrupt
};
/*
template <const Number interruptNumber> class Interrupt final {
  static constexpr auto scm_RegValue = cpp_register::reg_v<1UL, static_cast<InterruptT>(interruptNumber)>;

public:
  consteval Interrupt() = default;

  inline void Enable() const {
    using namespace stm32f0x0::nvic;
    NVIC->ISER |= NVIC_ISER::SETENA(scm_RegValue);
  }

  inline void Disable() const {
    using namespace stm32f0x0::nvic;
    NVIC->ICER |= NVIC_ICER::CLRENA(scm_RegValue);
  }

  inline void PendingSet() const {
    using namespace stm32f0x0::nvic;
    NVIC->ISPR |= NVIC_ISPR::SETPEND(scm_RegValue);
  }

  inline void PendingClear() const {
    using namespace stm32f0x0::nvic;
    NVIC->ICPR |= NVIC_ICPR::CLRPEND(scm_RegValue);
  }

  [[nodiscard]] inline bool Status() const {
    using namespace stm32f0x0::nvic;
    return (NVIC->ISER & NVIC_ISER::SETENA(scm_RegValue));
  }

  [[nodiscard]] inline bool PendingStatus() const {
    using namespace stm32f0x0::nvic;
    return (NVIC->ISPR & NVIC_ISPR::SETPEND(scm_RegValue));
  }
};

class InterruptController final {
  InterruptController(const InterruptController &) = delete;
  InterruptController &operator=(const InterruptController &) = delete;
  InterruptController(InterruptController &&) = delete;
  InterruptController &operator=(InterruptController &&) = delete;

  template <iso::const_value First>
  requires std::same_as<Number, typename First::type>
  [[nodiscard("The value have to be written to the register!")]] static inline consteval InterruptT Extract(const First) {
    return static_cast<InterruptT>(1UL << static_cast<InterruptT>(First::value));
  }

  template <iso::const_value First, iso::const_value... Rest>
  requires std::same_as<Number, typename First::type>
  [[nodiscard("The value have to be written to the register!")]] static inline consteval InterruptT Extract(const First, const Rest...) {
    return static_cast<InterruptT>(1UL << static_cast<InterruptT>(First::value)) | Extract(Rest{}...);
  }

public:
  consteval InterruptController() = default;

  template <iso::const_value InterruptNumber>
  requires std::same_as<Number, typename InterruptNumber::type>
  inline consteval Interrupt<InterruptNumber::value> operator[](const InterruptNumber) const {
    return Interrupt<InterruptNumber::value>{};
  }

  template <iso::const_value First, iso::const_value... Rest> inline void Enable(const First, const Rest...) const {
    using namespace stm32f0x0::nvic;
    constexpr auto value = Extract(First{}, Rest{}...);
    NVIC->ISER |= NVIC_ISER::SETENA(cpp_register::reg_v<value>);
  }

  template <iso::const_value First, iso::const_value... Rest> inline void Disable(const First, const Rest...) const {
    using namespace stm32f0x0::nvic;
    constexpr auto value = Extract(First{}, Rest{}...);
    NVIC->ICER |= NVIC_ICER::CLRENA(cpp_register::reg_v<value>);
  }

  template <iso::const_value First, iso::const_value... Rest> inline void PendingSet(const First, const Rest...) const {
    using namespace stm32f0x0::nvic;
    constexpr auto value = Extract(First{}, Rest{}...);
    NVIC->ISPR |= NVIC_ISPR::SETPEND(cpp_register::reg_v<value>);
  }

  template <iso::const_value First, iso::const_value... Rest> inline void PendingClear(const First, const Rest...) const {
    using namespace stm32f0x0::nvic;
    constexpr auto value = Extract(First{}, Rest{}...);
    NVIC->ICPR |= NVIC_ICPR::CLRPEND(cpp_register::reg_v<value>);
  }

  inline void GlobalEnable() const { asm volatile("cpsie i"); }
  inline void GlobalDisable() const { asm volatile("cpsid i"); }
};
*/

}; // namespace stm32f0x0::hal::interrupt