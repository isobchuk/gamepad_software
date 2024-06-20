#pragma once

#include <type_traits>

#include "fifo.hpp"
#include "reg_rcc.hpp"
#include "reg_syscfg.hpp"
#include "reg_usb.hpp"

#include "endpoint.hpp"

namespace stm32f0x0::usb {

class Usb final {
  template <const unsigned number> static inline constexpr bool _EP_MAX_NUMBER = (number < 8);

  template <const unsigned number>
  requires _EP_MAX_NUMBER<number>
  static inline constexpr auto _EP_NUMBER = cpp_register::reg_v<number>;

  enum class EndpointType : uint16_t { Bulk, Control, Interrupt, Isochronous };

  template <const EndpointType type>
  static inline constexpr auto _EP_TYPE = cpp_register::reg_v<static_cast<std::underlying_type_t<EndpointType>>(type)>;

  static constexpr std::size_t _PACKET_MEMORY_ADDRESS = 0x40006000UL;
  static constexpr std::size_t _MESSAGE_MEMORY_ADDRESS = 0x40UL;

  enum class EInterruptReason : uint16_t {
    LowPowerMode = (1U << 7),
    ExpectedStartOfFrame = (1U << 8),
    StartOfFrame = (1U << 9),
    Reset = (1U << 10),
    SuspendModeRequest = (1U << 11),
    WakeUp = (1U << 12),
    Error = (1U << 13),
    PacketMemoryError = (1U << 14),
    CorrectTransfer = (1U << 15)

  };
  struct SInterruptTable {
    const EInterruptReason mReason;
    void (&mInterruptHandler)(void);
  };

  using SControlEndpoint = iso::usb::endpoint::CEndpoint<8U>;
  static volatile SControlEndpoint sControlEndpointReceiveBuffer;

  static void Reset() {
    using namespace cpp_register;

    // Clear the interrupt flag
    USB->ISTR &= USB_ISTR::RESET;

    // Ep0 (Control) Initialize
    constexpr auto EP = _EP_NUMBER<0U>;
    constexpr auto EP_TYPE = _EP_TYPE<EndpointType::Control>;
    constexpr auto EP_BUFFER_SIZE = 64U;

    USB_BUFFER->USB_ADDRn_TX[EP] = USB_ADDRn_TX::ADDRn_TX(reg_v<_MESSAGE_MEMORY_ADDRESS>);
    USB_BUFFER->USB_ADDRn_RX[EP] = USB_ADDRn_RX::ADDRn_RX(reg_v<_MESSAGE_MEMORY_ADDRESS + EP_BUFFER_SIZE>);
    USB_BUFFER->USB_COUNTn_TX[EP] = USB_COUNTn_TX::COUNTn_TX(constants::ZERO);
    USB_BUFFER->USB_COUNTn_RX[EP] = USB_COUNTn_RX::BLSIZE | USB_COUNTn_RX::NUM_BLOCK(reg_v<EP_BUFFER_SIZE / 32 - 1>);

    USB->EPR[EP] = USB_EPR::EP_TYPE(EP_TYPE);

    USB->EPR[EP] ^= USB_EPR::DTOG_RX | USB_EPR::DTOG_TX | USB_EPR::STAT_TX | USB_EPR::STAT_RX;
    USB->DADDR |= USB_DADDR::EF;
  }

  static void CorrectTransfer() {
    using namespace cpp_register;
    if (sControlEndpointReceiveBuffer.bNumber == (USB->ISTR & USB_ISTR::EP_ID(reg_v<0b1111U>))) {
      if (USB->ISTR & USB_ISTR::DIR) {
        sControlEndpointReceiveBuffer.sLength = USB_BUFFER->USB_COUNTn_RX[reg_v<0U>] & USB_COUNTn_RX::COUNTn_RX(reg_v<0xFFU>);
        const uint8_t *data = reinterpret_cast<const uint8_t *>(0x40006080UL);
        for (unsigned i = 0; i < sControlEndpointReceiveBuffer.sLength; i++) {
          sControlEndpointReceiveBuffer.aBuffer[i] = data[i];
        }
      }
    }
  }

  static constexpr SInterruptTable sInterruptHandler[] = {{EInterruptReason::Reset, Reset}, {EInterruptReason::CorrectTransfer, CorrectTransfer}};

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

  inline auto &Read() const { return sControlEndpointReceiveBuffer; }

  static inline void InterruptHandler() {
    using namespace cpp_register;

    const auto interruptReason = USB->ISTR & (USB_ISTR::L1REQ | USB_ISTR::ESOF | USB_ISTR::SOF | USB_ISTR::RESET | USB_ISTR::SUSP | USB_ISTR::WKUP |
                                              USB_ISTR::ERR | USB_ISTR::PMAOVR | USB_ISTR::CTR);

    for (const auto &handler : sInterruptHandler) {
      // To handle several reasons concurrently - do not break from the loop
      if ((static_cast<std::underlying_type_t<EInterruptReason>>(handler.mReason) & interruptReason)) {
        handler.mInterruptHandler();
      }
    }
  }
};

} // namespace stm32f0x0::usb