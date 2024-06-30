#pragma once

#include "register.hpp"

namespace stm32f0x0::usb {

template <const cpp_register::RegisterAddress address> struct USB_T {
  static constexpr cpp_register::Register<address + 0x0, cpp_register::AccessMode::RW, uint32_t, struct EPR, 8, 4> EPR{};
  static constexpr cpp_register::Register<address + 0x40, cpp_register::AccessMode::RW, uint16_t, struct CNTR> CNTR{};
  static constexpr cpp_register::Register<address + 0x44, cpp_register::AccessMode::RW, uint16_t, struct ISTR> ISTR{};
  static constexpr cpp_register::Register<address + 0x48, cpp_register::AccessMode::R, uint16_t, struct FNR> FNR{};
  static constexpr cpp_register::Register<address + 0x4C, cpp_register::AccessMode::RW, uint16_t, struct DADDR> DADDR{};
  static constexpr cpp_register::Register<address + 0x50, cpp_register::AccessMode::RW, uint16_t, struct BTABLE> BTABLE{};
  static constexpr cpp_register::Register<address + 0x54, cpp_register::AccessMode::RW, uint16_t, struct LPMCSR> LPMCSR{};
  static constexpr cpp_register::Register<address + 0x58, cpp_register::AccessMode::RW, uint16_t, struct BCDR> BCDR{};
};

inline constexpr USB_T<0x40005C00> const *USB{};

struct USB_EPR {
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 0), cpp_register::AccessMode::RW, 4> EA{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 4), cpp_register::AccessMode::RW, 2> STAT_TX{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 6), cpp_register::AccessMode::RW, 1> DTOG_TX{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 7), cpp_register::AccessMode::RC_W0, 1> CTR_TX{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 8), cpp_register::AccessMode::RW, 1> EP_KIND{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 9), cpp_register::AccessMode::RW, 2> EP_TYPE{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 11), cpp_register::AccessMode::R, 1> SETUP{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 12), cpp_register::AccessMode::RW, 2> STAT_RX{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 14), cpp_register::AccessMode::RW, 1> DTOG_RX{};
  static constexpr cpp_register::Field<decltype(USB->EPR), (1UL << 15), cpp_register::AccessMode::RC_W0, 1> CTR_RX{};
};

struct USB_CNTR {
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 0), cpp_register::AccessMode::RW, 1> FRES{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 1), cpp_register::AccessMode::RW, 1> PDWN{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 2), cpp_register::AccessMode::RW, 1> LPMODE{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 3), cpp_register::AccessMode::RW, 1> FSUSP{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 4), cpp_register::AccessMode::RW, 1> RESUME{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 5), cpp_register::AccessMode::RW, 1> L1RESUME{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 7), cpp_register::AccessMode::RW, 1> L1REQM{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 8), cpp_register::AccessMode::RW, 1> ESOFM{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 9), cpp_register::AccessMode::RW, 1> SOFM{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 10), cpp_register::AccessMode::RW, 1> RESETM{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 11), cpp_register::AccessMode::RW, 1> SUSPM{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 12), cpp_register::AccessMode::RW, 1> WKUPM{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 13), cpp_register::AccessMode::RW, 1> ERRM{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 14), cpp_register::AccessMode::RW, 1> PMAOVRM{};
  static constexpr cpp_register::Field<decltype(USB->CNTR), (1UL << 15), cpp_register::AccessMode::RW, 1> CTRM{};
};

struct USB_ISTR {
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 0), cpp_register::AccessMode::R, 4> EP_ID{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 4), cpp_register::AccessMode::R, 1> DIR{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 7), cpp_register::AccessMode::RC_W0, 1> L1REQ{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 8), cpp_register::AccessMode::RC_W0, 1> ESOF{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 9), cpp_register::AccessMode::RC_W0, 1> SOF{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 10), cpp_register::AccessMode::RC_W0, 1> RESET{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 11), cpp_register::AccessMode::RC_W0, 1> SUSP{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 12), cpp_register::AccessMode::RC_W0, 1> WKUP{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 13), cpp_register::AccessMode::RC_W0, 1> ERR{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 14), cpp_register::AccessMode::RC_W0, 1> PMAOVR{};
  static constexpr cpp_register::Field<decltype(USB->ISTR), (1UL << 15), cpp_register::AccessMode::R, 1> CTR{};
};

struct USB_FNR {
  static constexpr cpp_register::Field<decltype(USB->FNR), (1UL << 0), cpp_register::AccessMode::R, 11> FN{};
  static constexpr cpp_register::Field<decltype(USB->FNR), (1UL << 11), cpp_register::AccessMode::R, 2> LSOF{};
  static constexpr cpp_register::Field<decltype(USB->FNR), (1UL << 13), cpp_register::AccessMode::R, 1> LCK{};
  static constexpr cpp_register::Field<decltype(USB->FNR), (1UL << 14), cpp_register::AccessMode::R, 1> RXDM{};
  static constexpr cpp_register::Field<decltype(USB->FNR), (1UL << 15), cpp_register::AccessMode::R, 1> RXDP{};
};

struct USB_DADDR {
  static constexpr cpp_register::Field<decltype(USB->DADDR), (1UL << 0), cpp_register::AccessMode::RW, 7> ADD{};
  static constexpr cpp_register::Field<decltype(USB->DADDR), (1UL << 7), cpp_register::AccessMode::RW, 1> EF{};
};

struct USB_BTABLE {
  static constexpr cpp_register::Field<decltype(USB->BTABLE), (1UL << 3), cpp_register::AccessMode::RW, 13> BTABLE{};
};

struct USB_LPMCSR {
  static constexpr cpp_register::Field<decltype(USB->LPMCSR), (1UL << 0), cpp_register::AccessMode::RW, 1> LPMEN{};
  static constexpr cpp_register::Field<decltype(USB->LPMCSR), (1UL << 1), cpp_register::AccessMode::RW, 1> LPMACK{};
  static constexpr cpp_register::Field<decltype(USB->LPMCSR), (1UL << 3), cpp_register::AccessMode::R, 1> REMWAKE{};
  static constexpr cpp_register::Field<decltype(USB->LPMCSR), (1UL << 4), cpp_register::AccessMode::R, 4> BESL{};
};

struct USB_BCDR {
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 0), cpp_register::AccessMode::RW, 1> BCDEN{};
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 1), cpp_register::AccessMode::RW, 1> DCDEN{};
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 2), cpp_register::AccessMode::RW, 1> PDEN{};
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 3), cpp_register::AccessMode::RW, 1> SDEN{};
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 4), cpp_register::AccessMode::R, 1> DCDET{};
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 5), cpp_register::AccessMode::R, 1> PDET{};
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 6), cpp_register::AccessMode::R, 1> SDET{};
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 7), cpp_register::AccessMode::R, 1> PS2DET{};
  static constexpr cpp_register::Field<decltype(USB->BCDR), (1UL << 15), cpp_register::AccessMode::RW, 1> DPPU{};
};

template <const cpp_register::RegisterAddress address> struct USB_BUFFER_T {
  static constexpr cpp_register::Register<address + 0x0, cpp_register::AccessMode::RW, uint16_t, struct USB_ADDRn_TX, 8U, 8U> USB_ADDRn_TX{};
  static constexpr cpp_register::Register<address + 0x2, cpp_register::AccessMode::RW, uint16_t, struct USB_COUNTn_TX, 8U, 8U> USB_COUNTn_TX{};
  static constexpr cpp_register::Register<address + 0x4, cpp_register::AccessMode::RW, uint16_t, struct USB_ADDRn_RX, 8U, 8U> USB_ADDRn_RX{};
  static constexpr cpp_register::Register<address + 0x6, cpp_register::AccessMode::RW, uint16_t, struct USB_COUNTn_RX, 8U, 8U> USB_COUNTn_RX{};
};

inline constexpr USB_BUFFER_T<0x40006000> const *USB_BUFFER{};

struct USB_ADDRn_TX {
  static constexpr cpp_register::Field<decltype(USB_BUFFER->USB_ADDRn_TX), (1UL << 0), cpp_register::AccessMode::RW, 15> ADDRn_TX{};
};

struct USB_COUNTn_TX {
  static constexpr cpp_register::Field<decltype(USB_BUFFER->USB_COUNTn_TX), (1UL << 0), cpp_register::AccessMode::RW, 10> COUNTn_TX{};
};

struct USB_ADDRn_RX {
  static constexpr cpp_register::Field<decltype(USB_BUFFER->USB_ADDRn_RX), (1UL << 0), cpp_register::AccessMode::RW, 15> ADDRn_RX{};
};

struct USB_COUNTn_RX {
  static constexpr cpp_register::Field<decltype(USB_BUFFER->USB_COUNTn_RX), (1UL << 0), cpp_register::AccessMode::R, 10> COUNTn_RX{};
  static constexpr cpp_register::Field<decltype(USB_BUFFER->USB_COUNTn_RX), (1UL << 10), cpp_register::AccessMode::RW, 5> NUM_BLOCK{};
  static constexpr cpp_register::Field<decltype(USB_BUFFER->USB_COUNTn_RX), (1UL << 15), cpp_register::AccessMode::RW, 1> BLSIZE{};
};

} // namespace stm32f0x0::usb
