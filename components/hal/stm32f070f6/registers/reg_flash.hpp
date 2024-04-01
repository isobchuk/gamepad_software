#pragma once

#include "register.hpp"

namespace stm32f0x0::flash {

template <const cpp_register::RegisterAddress address> struct FLASH_T {
  static constexpr cpp_register::Register<address + 0x0, cpp_register::AccessMode::RW, uint32_t, struct ACR> ACR{};
  static constexpr cpp_register::Register<address + 0x4, cpp_register::AccessMode::W, uint32_t, struct KEYR> KEYR{};
  static constexpr cpp_register::Register<address + 0x8, cpp_register::AccessMode::W, uint32_t, struct OPTKEYR> OPTKEYR{};
  static constexpr cpp_register::Register<address + 0xC, cpp_register::AccessMode::RW, uint32_t, struct SR> SR{};
  static constexpr cpp_register::Register<address + 0x10, cpp_register::AccessMode::RW, uint32_t, struct CR> CR{};
  static constexpr cpp_register::Register<address + 0x14, cpp_register::AccessMode::W, uint32_t, struct AR> AR{};
  static constexpr cpp_register::Register<address + 0x1C, cpp_register::AccessMode::R, uint32_t, struct OBR> OBR{};
  static constexpr cpp_register::Register<address + 0x20, cpp_register::AccessMode::R, uint32_t, struct WRPR> WRPR{};
};

inline constexpr FLASH_T<0x40022000> const *FLASH{};

struct FLASH_ACR {
  static constexpr cpp_register::Field<decltype(FLASH->ACR), (1UL << 0), cpp_register::AccessMode::RW, 3> LATENCY{};
  static constexpr cpp_register::Field<decltype(FLASH->ACR), (1UL << 4), cpp_register::AccessMode::RW, 1> PRFTBE{};
  static constexpr cpp_register::Field<decltype(FLASH->ACR), (1UL << 5), cpp_register::AccessMode::R, 1> PRFTBS{};
};

struct FLASH_KEYR {
  static constexpr cpp_register::Field<decltype(FLASH->KEYR), (1UL << 0), cpp_register::AccessMode::W, 32> FKEYR{};
};

struct FLASH_OPTKEYR {
  static constexpr cpp_register::Field<decltype(FLASH->OPTKEYR), (1UL << 0), cpp_register::AccessMode::W, 32> OPTKEYR{};
};

struct FLASH_SR {
  static constexpr cpp_register::Field<decltype(FLASH->SR), (1UL << 5), cpp_register::AccessMode::RC_W1, 1> EOP{};
  static constexpr cpp_register::Field<decltype(FLASH->SR), (1UL << 4), cpp_register::AccessMode::RC_W1, 1> WRPRT{};
  static constexpr cpp_register::Field<decltype(FLASH->SR), (1UL << 2), cpp_register::AccessMode::RC_W1, 1> PGERR{};
  static constexpr cpp_register::Field<decltype(FLASH->SR), (1UL << 0), cpp_register::AccessMode::R, 1> BSY{};
};

struct FLASH_CR {
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 13), cpp_register::AccessMode::RW, 1> FORCE_OPTLOAD{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 12), cpp_register::AccessMode::RW, 1> EOPIE{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 10), cpp_register::AccessMode::RW, 1> ERRIE{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 9), cpp_register::AccessMode::RW, 1> OPTWRE{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 7), cpp_register::AccessMode::RW, 1> LOCK{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 6), cpp_register::AccessMode::RW, 1> STRT{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 5), cpp_register::AccessMode::RW, 1> OPTER{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 4), cpp_register::AccessMode::RW, 1> OPTPG{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 2), cpp_register::AccessMode::RW, 1> MER{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 1), cpp_register::AccessMode::RW, 1> PER{};
  static constexpr cpp_register::Field<decltype(FLASH->CR), (1UL << 0), cpp_register::AccessMode::RW, 1> PG{};
};

struct FLASH_AR {
  static constexpr cpp_register::Field<decltype(FLASH->AR), (1UL << 0), cpp_register::AccessMode::W, 32> FAR{};
};

struct FLASH_OBR {
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 0), cpp_register::AccessMode::R, 1> OPTERR{};
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 1), cpp_register::AccessMode::R, 2> RDPRT{};
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 8), cpp_register::AccessMode::R, 1> WDG_SW{};
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 9), cpp_register::AccessMode::R, 1> nRST_STOP{};
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 10), cpp_register::AccessMode::R, 1> nRST_STDBY{};
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 12), cpp_register::AccessMode::R, 1, 2> nBOOT1{};
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 13), cpp_register::AccessMode::R, 1> VDDA_MONITOR{};
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 14), cpp_register::AccessMode::R, 1> RAM_PARITY_CHECK{};
  static constexpr cpp_register::Field<decltype(FLASH->OBR), (1UL << 16), cpp_register::AccessMode::R, 8, 2> Data{};
};

struct FLASH_WRPR {
  static constexpr cpp_register::Field<decltype(FLASH->WRPR), (1UL << 0), cpp_register::AccessMode::R, 32> WRP{};
};

} // namespace stm32f0x0::flash
