#pragma once

#include "hal_systick.hpp"
#include "reg_stk.hpp"
#include <type_traits>

namespace stm32f0x0::system_timer {

template <typename TimeSinceLaunchT>
concept time_since_launch = requires(TimeSinceLaunchT time) { time + 1; } || std::same_as<TimeSinceLaunchT, void>;

enum class Unit : uint32_t { uS = 1UL, mS = 1000UL, S = 1000000UL };

template <const uint32_t systemFrequency, const Unit unit, time_since_launch SystemTimeCounter = void> class SystemTimer final {
  static constexpr bool mIsInterruptEnabled = !std::is_same_v<void, SystemTimeCounter>;

  static constexpr auto mReloadPeriod = cpp_register::reg_v<systemFrequency / static_cast<uint32_t>(unit) - 1>;
  static constexpr auto mInterruptEnable = cpp_register::reg_v<(mIsInterruptEnabled ? 1UL : 0UL)>;

  template <typename T, typename Dummy = void> struct SystemTime {
    static volatile T mSystemTime;
  };
  template <typename Dummy> struct SystemTime<void, Dummy> {};

  using TimeSinceLaunch = SystemTime<SystemTimeCounter>;

public:
  using SystemTimeCounterT = SystemTimeCounter;
  consteval SystemTimer() {
    static_assert(::hal::system_timer::system_timer<SystemTimer>, "The class system timer should implement a whole concept interface!");
    if constexpr (mIsInterruptEnabled) {
      static_assert(::hal::system_timer::system_timer_interrupt<SystemTimer>,
                    "The class system timer INTERRUPT should implement a whole concept interface!");
    }
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

  [[nodiscard]] inline SystemTimeCounterT Time() const
  requires mIsInterruptEnabled
  {
    return TimeSinceLaunch::mSystemTime;
  }

  static inline void InterruptHandler()
  requires mIsInterruptEnabled
  {
    if constexpr (mIsInterruptEnabled) {
      TimeSinceLaunch::mSystemTime = TimeSinceLaunch::mSystemTime + 1;
    }
  }
};

template <const uint32_t systemFrequency, const Unit unit, time_since_launch SystemTimeCounter>
template <typename T, typename Dummy>
volatile T SystemTimer<systemFrequency, unit, SystemTimeCounter>::SystemTime<T, Dummy>::mSystemTime;

} // namespace stm32f0x0::system_timer