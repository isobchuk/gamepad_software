#pragma once

#include <concepts>

namespace hal::system_timer {
template <typename SystemTimerT>
concept system_timer = requires(const SystemTimerT syst) {
  { syst.Init() } -> std::same_as<void>;
  { syst.CountFlag() } -> std::same_as<bool>;
};

}