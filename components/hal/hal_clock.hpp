#pragma once

#include <concepts>

namespace hal::clock {
template <typename SystemFrequencyT>
concept system_frequency = std::unsigned_integral<SystemFrequencyT> && (sizeof(SystemFrequencyT) >= sizeof(unsigned long));

template <typename SystemClockT>
concept system_clock = requires(SystemClockT cl) {
  cl.Init();
  { cl.Frequency() } -> system_frequency;
};
}; // namespace hal::clock