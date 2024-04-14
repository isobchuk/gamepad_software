#pragma once

namespace system_time {
using Tick = unsigned long;

struct TimeoutTimer {
  Tick timeout;
  bool enable;

  TimeoutTimer() : timeout(), enable(false) {}
};

class SystemTime final {
  SystemTime(const SystemTime &) = delete;
  SystemTime &operator=(const SystemTime &) = delete;
  SystemTime(SystemTime &&) = delete;
  SystemTime &operator=(SystemTime &&) = delete;

  const volatile Tick &mTime;

public:
  consteval SystemTime(const volatile Tick &pTime) : mTime(pTime) {}

  inline void Start(TimeoutTimer &pTimeout) const {
    if (false == pTimeout.enable) {
      pTimeout.timeout = mTime;
      pTimeout.enable = true;
    }
  }

  [[nodiscard]] inline bool Check(TimeoutTimer &pTimeout, const Tick &pValue) const {
    bool result = false;

    if (true == pTimeout.enable) {
      if ((mTime - pTimeout.timeout) >= (pValue)) {
        result = true;
        pTimeout.enable = false;
      }
    }

    return result;
  }

  inline void Delay(const Tick &pValue) const {
    const Tick currentTime = mTime;
    while ((pValue) > (mTime - currentTime)) {
      continue;
    }
  }

  inline Tick Time() const { return mTime; }
};
} // namespace system_time
