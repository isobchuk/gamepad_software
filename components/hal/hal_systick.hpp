#pragma once

#include <concepts>

namespace hal::system_timer {
template <typename SystemTimerT>
concept system_timer = requires(const SystemTimerT syst) {
  { syst.Init() } -> std::same_as<void>;
  { syst.CountFlag() } -> std::same_as<bool>;
};

template <typename SystemTimerT>
concept system_timer_interrupt = requires(const SystemTimerT syst) {
  { syst.Time() } -> std::same_as<typename SystemTimerT::SystemTimeCounterT>;
  { SystemTimerT::InterruptHandler() } -> std::same_as<void>;
  typename SystemTimerT::SystemTimeCounterT;
};

template <typename SystemTimerT>
concept system_timer_launch = system_timer<SystemTimerT> && system_timer_interrupt<SystemTimerT>;

} // namespace hal::system_timer