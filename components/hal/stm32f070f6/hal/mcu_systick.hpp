#pragma once

#include "hal_systick.hpp"
#include "reg_stk.hpp"

namespace stm32f0x0::system_timer {

template <typename TimeSinceLaunchT>
concept time_since_launch = requires(TimeSinceLaunchT time) { time++; };

template <const uint32_t reloadPeriod, const bool interrupt = false> class SystemTimer final {
  static constexpr auto mReloadPeriod = cpp_register::reg_v<reloadPeriod>;
  static constexpr auto mInterruptEnable = cpp_register::reg_v<((interrupt) ? 1UL : 0UL)>;

public:
  consteval SystemTimer() {
    static_assert(::hal::system_timer::system_timer<SystemTimer>, "The class system timer should implement a whole concept interface!");
  }

  inline void Init() const {
    using namespace stm32f0x0::stk;
    STK->RVR = STK_RVR::RELOAD(mReloadPeriod);
    STK->CVR = STK_CVR::CURRENT(mReloadPeriod);
    STK->CSR |= (STK_CSR::CLKSOURCE | STK_CSR::TICKINT(mInterruptEnable) | STK_CSR::ENABLE);
  }

  [[nodiscard]] inline bool CountFlag(void) const {
    using namespace stm32f0x0::stk;
    return (STK->CSR & STK_CSR::COUNTFLAG);
  }

  // static constexpr
};
} // namespace stm32f0x0::system_timer