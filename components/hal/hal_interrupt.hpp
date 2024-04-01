#pragma once

#include "meta_types.hpp"
#include <concepts>


namespace hal::interrupt {
template <typename InterruptT>
concept interrupt = requires(const InterruptT intr) {
  { intr.Enable() } -> std::same_as<void>;
  { intr.Disable() } -> std::same_as<void>;
  { intr.PendingSet() } -> std::same_as<void>;
  { intr.PendingClear() } -> std::same_as<void>;
  { intr.Status() } -> std::same_as<bool>;
  { intr.PendingStatus() } -> std::same_as<bool>;
  typename InterruptT::InterruptType;
};

template <typename InterruptT>
concept is_interrupt = requires(const InterruptT) { typename InterruptT::InterruptType; };

template <typename InterruptControllerT>
concept interrupt_controller = requires(const InterruptControllerT intrController) {
  typename InterruptControllerT::InterruptNumber;
  { intrController.GlobalEnable() } -> std::same_as<void>;
  { intrController.GlobalDisable() } -> std::same_as<void>;

  { intrController[iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>] } -> is_interrupt;
  {
    intrController.Enable(iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>,
                          iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>)
  } -> std::same_as<void>;
  {
    intrController.Disable(iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>,
                           iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>)
  } -> std::same_as<void>;
  {
    intrController.PendingSet(iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>,
                              iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>)
  } -> std::same_as<void>;
  {
    intrController.PendingClear(iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>,
                                iso::meta_type::const_v<typename InterruptControllerT::InterruptNumber{}>)
  } -> std::same_as<void>;
};
} // namespace hal::interrupt