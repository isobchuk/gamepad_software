#pragma once

#include "register.hpp"

namespace stm32f0x0::gpio {

template <const cpp_register::RegisterAddress address> struct GPIO_T {
	static constexpr cpp_register::Register<address + 0x0, cpp_register::AccessMode::RW, uint32_t, struct MODER> MODER{};
	static constexpr cpp_register::Register<address + 0x4, cpp_register::AccessMode::RW, uint32_t, struct OTYPER> OTYPER{};
	static constexpr cpp_register::Register<address + 0x8, cpp_register::AccessMode::RW, uint32_t, struct OSPEEDR> OSPEEDR{};
	static constexpr cpp_register::Register<address + 0xC, cpp_register::AccessMode::RW, uint32_t, struct PUPDR> PUPDR{};
	static constexpr cpp_register::Register<address + 0x10, cpp_register::AccessMode::R, uint32_t, struct IDR> IDR{};
	static constexpr cpp_register::Register<address + 0x14, cpp_register::AccessMode::RW, uint32_t, struct ODR> ODR{};
	static constexpr cpp_register::Register<address + 0x18, cpp_register::AccessMode::W, uint32_t, struct BSRR> BSRR{};
	static constexpr cpp_register::Register<address + 0x1C, cpp_register::AccessMode::RW, uint32_t, struct LCKR> LCKR{};
	static constexpr cpp_register::Register<address + 0x20, cpp_register::AccessMode::RW, uint32_t, struct AFR, 2> AFR{};
};

inline constexpr GPIO_T<0x48001400> const *GPIOF{};
inline constexpr GPIO_T<0x48000C00> const *GPIOD{};
inline constexpr GPIO_T<0x48000800> const *GPIOC{};
inline constexpr GPIO_T<0x48000400> const *GPIOB{};
inline constexpr GPIO_T<0x48000000> const *GPIOA{};


 struct GPIO_MODER {
	static constexpr cpp_register::Field<decltype(GPIOF->MODER), (1UL << 0), cpp_register::AccessMode::RW, 2, 16> MODER{};
};

struct GPIO_OTYPER {
	static constexpr cpp_register::Field<decltype(GPIOF->OTYPER), (1UL << 0), cpp_register::AccessMode::RW, 1, 16> OT{};
};

struct GPIO_OSPEEDR {
	static constexpr cpp_register::Field<decltype(GPIOF->OSPEEDR), (1UL << 0), cpp_register::AccessMode::RW, 2, 16> OSPEEDR{};
};

struct GPIO_PUPDR {
	static constexpr cpp_register::Field<decltype(GPIOF->PUPDR), (1UL << 0), cpp_register::AccessMode::RW, 2, 16> PUPDR{};
};

struct GPIO_IDR {
	static constexpr cpp_register::Field<decltype(GPIOF->IDR), (1UL << 0), cpp_register::AccessMode::R, 1, 16> IDR{};
};

struct GPIO_ODR {
	static constexpr cpp_register::Field<decltype(GPIOF->ODR), (1UL << 0), cpp_register::AccessMode::RW, 1, 16> ODR{};
};

struct GPIO_BSRR {
	static constexpr cpp_register::Field<decltype(GPIOF->BSRR), (1UL << 16), cpp_register::AccessMode::W, 1, 16> BR{};
	static constexpr cpp_register::Field<decltype(GPIOF->BSRR), (1UL << 0), cpp_register::AccessMode::W, 1, 16> BS{};
};

struct GPIO_LCKR {
	static constexpr cpp_register::Field<decltype(GPIOF->LCKR), (1UL << 16), cpp_register::AccessMode::RW, 1> LCKK{};
	static constexpr cpp_register::Field<decltype(GPIOF->LCKR), (1UL << 0), cpp_register::AccessMode::RW, 1, 16> LCK{};
};

struct GPIO_AFR {
	static constexpr cpp_register::Field<decltype(GPIOF->AFR), (1UL << 0), cpp_register::AccessMode::RW, 4, 8> AFR{};
};

}
