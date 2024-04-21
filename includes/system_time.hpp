#pragma once

// Not finished component

#include "hal_systick.hpp"

namespace system_time {

template <::hal::system_timer::system_timer_launch Timer> class SystemTime final {
  SystemTime(const SystemTime &) = delete;
  SystemTime &operator=(const SystemTime &) = delete;
  SystemTime(SystemTime &&) = delete;
  SystemTime &operator=(SystemTime &&) = delete;

  using TickT = Timer::SystemTimeCounterT;

  const Timer &mTimer;

public:
  struct TimeoutTimer {
    TickT timeout;
    bool enable;

    TimeoutTimer() : timeout(), enable(false) {}
  };

  consteval SystemTime(const Timer &pTimer) : mTimer(pTimer) {}

  inline void Start(TimeoutTimer &pTimeout) const {
    if (false == pTimeout.enable) {
      pTimeout.timeout = mTimer.Time();
      pTimeout.enable = true;
    }
  }

  [[nodiscard]] inline bool Check(TimeoutTimer &pTimeout, const TickT &pValue) const {
    bool result = false;

    if (true == pTimeout.enable) {
      if ((mTimer.Time() - pTimeout.timeout) >= (pValue)) {
        result = true;
        pTimeout.enable = false;
      }
    }

    return result;
  }

  inline void Delay(const TickT &pValue) const {
    const TickT currentTime = mTimer.Time();
    while ((pValue) > (mTimer.Time() - currentTime)) {
    }
  }

  inline TickT Time() const { return mTimer.Time(); }
};
} // namespace system_time
