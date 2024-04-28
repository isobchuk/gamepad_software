#pragma once

#include "reg_rcc.hpp"
#include "reg_syscfg.hpp"
#include "reg_usb.hpp"

namespace stm32f0x0::usb {

class Usb final {
public:
  consteval Usb() = default;
  inline void Init() const {
    using namespace stm32f0x0::rcc;
    using namespace stm32f0x0::syscfg;
    using namespace cpp_register;

    // Remap pins to use USB
    RCC->APB2ENR |= RCC_APB2ENR::SYSCFGEN;
    SYSCFG->CFGR1 |= SYSCFG_CFGR1::PA11_PA12_RMP;

    // Clock USB
    RCC->CFGR3 |= RCC_CFGR3::USBSW;
    RCC->APB1ENR |= RCC_APB1ENR::USBEN;

    // Add pull-up to DP
    USB->BCDR |= USB_BCDR::DPPU;
    USB->CNTR |= USB_CNTR::CTRM | USB_CNTR::RESETM;
    USB->CNTR &= USB_CNTR::PDWN;
    USB->CNTR &= USB_CNTR::FRES;
  }

  static inline void InterruptHandler() {
    using namespace cpp_register;

    // Check for reset
    if (USB->ISTR & USB_ISTR::RESET) {
      USB->ISTR &= USB_ISTR::RESET;

      // Ep
      USB_BUFFER->USB_ADDRn_TX[reg_v<0U>] = USB_ADDRn_TX::ADDRn_TX(reg_v<0x0040U>);
      USB_BUFFER->USB_ADDRn_RX[reg_v<0U>] = USB_ADDRn_RX::ADDRn_RX(reg_v<0x0080U>);
      USB_BUFFER->USB_COUNTn_TX[reg_v<0U>] = USB_COUNTn_TX::COUNTn_TX(reg_v<0U>);
      USB_BUFFER->USB_COUNTn_RX[reg_v<0U>] = USB_COUNTn_RX::BLSIZE | USB_COUNTn_RX::NUM_BLOCK(reg_v<1U>);

      USB->EPR[reg_v<0U>] = USB_EPR::EP_TYPE(reg_v<1U>);

      USB->EPR[reg_v<0U>] ^= USB_EPR::DTOG_RX | USB_EPR::DTOG_TX | USB_EPR::STAT_TX | USB_EPR::STAT_RX;
      USB->DADDR |= USB_DADDR::EF;
    }

    // Check for Transfer
    if (USB->ISTR & USB_ISTR::CTR) {
      const auto ep = USB->ISTR & USB_ISTR::EP_ID(reg_v<0b1111U>);
      if (0 == ep) {
        if (USB->ISTR & USB_ISTR::DIR) {
          const auto length = USB_BUFFER->USB_COUNTn_RX[reg_v<0U>] & USB_COUNTn_RX::COUNTn_RX(reg_v<0xFFU>);
          if (8 == length) {
            char buffer[8];
            for (unsigned i = 0U; i < 4; i++) {
              *(static_cast<volatile uint16_t *>(static_cast<volatile void *>(&(buffer))) + i) = *(reinterpret_cast<uint16_t *>(0x40006080UL) + i);
            }
          }
        }
      }
    }
  }
};

} // namespace stm32f0x0::usb