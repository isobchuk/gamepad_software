#pragma once

#include "register.hpp"

namespace stm32f0x0::nvic {

template <const cpp_register::RegisterAddress address> struct NVIC_T {
  static constexpr cpp_register::Register<address + 0x0, cpp_register::AccessMode::RS, uint32_t, struct ISER> ISER{};
  static constexpr cpp_register::Register<address + 0x80, cpp_register::AccessMode::RS, uint32_t, struct ICER> ICER{};
  static constexpr cpp_register::Register<address + 0x100, cpp_register::AccessMode::RS, uint32_t, struct ISPR> ISPR{};
  static constexpr cpp_register::Register<address + 0x180, cpp_register::AccessMode::RS, uint32_t, struct ICPR> ICPR{};
  static constexpr cpp_register::Register<address + 0x300, cpp_register::AccessMode::RW, uint32_t, struct IPR, 8U> IPR{};
};

inline constexpr NVIC_T<0xE000E100> const *NVIC{};

struct NVIC_ISER {
  static constexpr cpp_register::Field<decltype(NVIC->ISER), (1UL << 0), cpp_register::AccessMode::RS, 32> SETENA{};
};

struct NVIC_ICER {
  static constexpr cpp_register::Field<decltype(NVIC->ICER), (1UL << 0), cpp_register::AccessMode::RS, 32> CLRENA{};
};

struct NVIC_ISPR {
  static constexpr cpp_register::Field<decltype(NVIC->ISPR), (1UL << 0), cpp_register::AccessMode::RS, 32> SETPEND{};
};

struct NVIC_ICPR {
  static constexpr cpp_register::Field<decltype(NVIC->ICPR), (1UL << 0), cpp_register::AccessMode::RS, 32> CLRPEND{};
};

struct NVIC_IPR {
  static constexpr cpp_register::Field<decltype(NVIC->IPR), (1UL << 6), cpp_register::AccessMode::RW, 2, 4, 6> PRI_N{};
};

} // namespace stm32f0x0::nvic
