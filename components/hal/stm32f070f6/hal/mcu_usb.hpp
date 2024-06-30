#pragma once

#include <type_traits>

#include "fifo.hpp"
#include "reg_rcc.hpp"
#include "reg_syscfg.hpp"
#include "reg_usb.hpp"

#include "endpoint.hpp"
static volatile unsigned resetCtr;
static volatile unsigned resetCtr1;
static volatile unsigned Interrupt;
static volatile unsigned iHard = 0;

namespace stm32f0x0::usb {
template <const unsigned number> static inline constexpr bool _EP_MAX_NUMBER = (number < 8);

enum class EndpointType : uint16_t { Bulk, Control, Isochronous, Interrupt };

static constexpr std::size_t _PACKET_MEMORY_ADDRESS = 0x40006000UL;
static constexpr std::size_t _MESSAGE_MEMORY_ADDRESS = 0x40UL;
static constexpr std::size_t _MESSAGE_USER_SPACE = _MESSAGE_MEMORY_ADDRESS + 2 * 64;

template <iso::usb::endpoint::c_endpoint Buffer, const EndpointType type, const unsigned N, const unsigned address, const unsigned size>
requires _EP_MAX_NUMBER<N>
class Endpoint final {
  static constexpr auto _EP_TYPE = cpp_register::reg_v<static_cast<std::underlying_type_t<EndpointType>>(type)>;
  static constexpr auto _EP_NUMBER = cpp_register::reg_v<N>;
  static constexpr auto _EP_ADDRESS = address;
  static constexpr auto _EP_SIZE = size;

  static constexpr auto _ADDRESS_TX = _EP_ADDRESS;
  static constexpr auto _ADDRESS_RX = _EP_ADDRESS + _EP_SIZE;

  volatile Buffer _EndpointReceiveBuffer;
  volatile bool _SendConfirmed;

public:
  Endpoint() : _EndpointReceiveBuffer(N), _SendConfirmed(true) {}

  inline void Init() const volatile {
    using namespace cpp_register;

    USB_BUFFER->USB_ADDRn_TX[_EP_NUMBER] = USB_ADDRn_TX::ADDRn_TX(reg_v<_ADDRESS_TX>);
    USB_BUFFER->USB_ADDRn_RX[_EP_NUMBER] = USB_ADDRn_RX::ADDRn_RX(reg_v<_ADDRESS_RX>);
    USB_BUFFER->USB_COUNTn_TX[_EP_NUMBER] = USB_COUNTn_TX::COUNTn_TX(constants::ZERO);
    USB_BUFFER->USB_COUNTn_RX[_EP_NUMBER] = USB_COUNTn_RX::BLSIZE | USB_COUNTn_RX::NUM_BLOCK(reg_v<_EP_SIZE / 32 - 1>);

    USB->EPR[_EP_NUMBER] = USB_EPR::STAT_TX(reg_v<0b10U>) | USB_EPR::STAT_RX(reg_v<0b11U>) | USB_EPR::EP_TYPE(_EP_TYPE) | USB_EPR::EA(_EP_NUMBER);

    /*CStatus::SetValidRx();
    CStatus::SetValidTx();*/
  }

  inline bool CorrectTransfer() volatile {
    using namespace cpp_register;
    constexpr auto epMask = reg_v<0b1111U>;
    bool result = true;

    // Is message for us?
    if (_EndpointReceiveBuffer.bNumber == (USB->ISTR & USB_ISTR::EP_ID(epMask))) {
      if ((USB->ISTR & USB_ISTR::DIR)) {
        _EndpointReceiveBuffer.sLength = USB_BUFFER->USB_COUNTn_RX[_EP_NUMBER] & USB_COUNTn_RX::COUNTn_RX(reg_v<0xFFU>);
        const uint16_t *data = reinterpret_cast<const uint16_t *>(_PACKET_MEMORY_ADDRESS + _ADDRESS_RX);
        for (unsigned i = 0; i < (_EndpointReceiveBuffer.sLength + 1) / 2; i++) {
          reinterpret_cast<volatile uint16_t *>(_EndpointReceiveBuffer.aBuffer)[i] = data[i];
        }
        USB->EPR[_EP_NUMBER] &=
            USB_EPR::CTR_RX | USB_EPR::DTOG_RX | USB_EPR::STAT_RX(reg_v<0b11U>) | USB_EPR::DTOG_TX | USB_EPR::STAT_TX(reg_v<0b11U>);

        USB->EPR[_EP_NUMBER] = USB_EPR::DTOG_RX | USB_EPR::EP_TYPE(_EP_TYPE) | USB_EPR::EA(_EP_NUMBER);

        /*CStatus::CleanInterruptRx();
        CStatus::ChangeDtogTx();*/
        if (_EndpointReceiveBuffer.bNumber == 1) {
          resetCtr1 = resetCtr1 + 1;
        }
      } else {
        USB->EPR[_EP_NUMBER] &=
            USB_EPR::CTR_TX | USB_EPR::DTOG_RX | USB_EPR::STAT_RX(reg_v<0b11U>) | USB_EPR::DTOG_TX | USB_EPR::STAT_TX(reg_v<0b11U>);

        _SendConfirmed = true;

        /*CStatus::CleanInterruptTx();
        CStatus::ChangeDtogRx();*/
        if (_EndpointReceiveBuffer.bNumber == 1) {
          resetCtr = resetCtr + 1;
        } else {
          USB->EPR[_EP_NUMBER] = USB_EPR::DTOG_TX | USB_EPR::EP_TYPE(_EP_TYPE) | USB_EPR::EA(_EP_NUMBER);
        }
      }
    } else {
      result = false;
    }
    return result;
  }

  template <const unsigned arraySize> inline bool Write(const uint8_t (&buf)[arraySize], const unsigned number = arraySize) volatile {
    using namespace cpp_register;

    if (_SendConfirmed) {
      uint16_t *memory = reinterpret_cast<uint16_t *>(_PACKET_MEMORY_ADDRESS + _ADDRESS_TX);
      for (unsigned i = 0; i < (number + 1) / 2; i++) {
        memory[i] = reinterpret_cast<const uint16_t *>(buf)[i];
      }

      USB_BUFFER->USB_COUNTn_TX[_EP_NUMBER] = number;

      USB->EPR[_EP_NUMBER] = USB_EPR::STAT_TX(reg_v<0b01U>) | USB_EPR::EP_TYPE(_EP_TYPE) | USB_EPR::EA(_EP_NUMBER);

      _SendConfirmed = false;
    }
    /*CStatus::SetValidTx();
    CStatus::SetValidRx();*/

    return !_SendConfirmed;
  }

  inline bool WriteEmpty() volatile {
    using namespace cpp_register;
    if (_SendConfirmed) {
      USB_BUFFER->USB_COUNTn_TX[_EP_NUMBER] = USB_COUNTn_TX::COUNTn_TX(reg_v<0U>);

      USB->EPR[_EP_NUMBER] = USB_EPR::STAT_TX(reg_v<0b01U>) | USB_EPR::EP_TYPE(_EP_TYPE) | USB_EPR::EA(_EP_NUMBER);
      _SendConfirmed = false;
    };
    /*CStatus::ChangeDtogTx();
    CStatus::SetValidTx();
    CStatus::SetValidRx();*/
    return true;
  }

  inline volatile Buffer &Read() volatile { return _EndpointReceiveBuffer; }

  inline void Ack() volatile {
    using namespace cpp_register;
    USB->EPR[_EP_NUMBER] = USB_EPR::STAT_RX(reg_v<0b01U>) | USB_EPR::EP_TYPE(_EP_TYPE) | USB_EPR::EA(_EP_NUMBER);

    /*CStatus::SetValidRx();
     CStatus::SetNakTx();*/
  }
};

template <auto &...endpoints> class Usb final {

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
  using TEndpointControl = Endpoint<SControlEndpoint, EndpointType::Control, 0UL, _MESSAGE_MEMORY_ADDRESS, 64U>;
  static volatile TEndpointControl EndpointControl;

  static void Reset() {
    using namespace cpp_register;

    // Clear the interrupt flag
    USB->ISTR &= USB_ISTR::RESET;

    // Ep0 (Control) Initialize
    EndpointControl.Init();

    // Enable the Usb device
    USB->DADDR |= USB_DADDR::EF;
  }

  static void CorrectTransfer() {
    EndpointControl.CorrectTransfer();
    (endpoints.CorrectTransfer(), ...);
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

  auto ControlEndpoint() const -> decltype(EndpointControl) & { return EndpointControl; }

  inline void Address(const uint8_t addr) const {
    constexpr uint8_t enable = 1U << 7;
    USB->DADDR = static_cast<uint8_t>(enable | addr);
  }

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

template <auto &...endpoints> volatile Usb<endpoints...>::TEndpointControl Usb<endpoints...>::EndpointControl{};

} // namespace stm32f0x0::usb