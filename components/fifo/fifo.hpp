#pragma once

#include <concepts>
#include <functional>
#include <optional>
#include <type_traits>

namespace iso::buffer {

template <typename T>
concept fifo_t = requires(T buffer) {
  typename T::TFifo;
  typename T::value_t;

  { buffer.empty() } -> std::same_as<bool>;
  { buffer.full() } -> std::same_as<bool>;
  { buffer.count() } -> std::unsigned_integral;
  { buffer.size() } -> std::unsigned_integral;
  { buffer.flush() } -> std::same_as<void>;
  { buffer.push(typename T::value_t{}) } -> std::same_as<bool>;
  { buffer.push(*new typename T::value_t) } -> std::same_as<bool>;
  { buffer.fetch() } -> std::same_as<std::optional<std::reference_wrapper<const typename T::value_t>>>;
  { buffer.pop() } -> std::same_as<void>;
  { buffer.pull() } -> std::same_as<std::optional<std::reference_wrapper<const typename T::value_t>>>;
};

template <typename T, const unsigned sz>
requires std::copyable<T> && ((0 == (sz & (sz - 1))) && (0 != sz)) // Check that size is power of 2 and bigger than 0
class CFifo final {
  using fifo_size_t = decltype(sz);
  static constexpr fifo_size_t mSize = sz;
  static constexpr fifo_size_t mMask = sz - 1U;
  T mData[mSize];
  fifo_size_t mIndxIn;
  fifo_size_t mIndxOut;

public:
  struct TFifo;
  using value_t = T;

  inline CFifo() : mIndxIn(), mIndxOut() { static_assert(fifo_t<CFifo>, "The class should implement the whole fifo interface"); }

  [[nodiscard]] inline bool empty() const volatile { return mIndxIn == mIndxOut; }
  [[nodiscard]] inline bool full() const volatile { return (mIndxIn - mIndxOut) & static_cast<fifo_size_t>(~mMask); }
  [[nodiscard]] inline fifo_size_t count() const volatile { return (mIndxIn - mIndxOut) & mMask; }
  [[nodiscard]] inline consteval fifo_size_t size() const volatile { return mSize; }
  inline void flush() volatile { mIndxIn = mIndxOut = 0U; }

  inline bool push(const volatile T &&value) volatile {
    if (full()) {
      return false;
    }

    mData[mIndxIn & mMask] = value;
    mIndxIn = mIndxIn + 1;
    return true;
  }

  inline bool push(const volatile T &value) volatile {
    if (full()) {
      return false;
    }

    mData[mIndxIn & mMask] = value;
    mIndxIn = mIndxIn + 1;
    return true;
  }

  inline bool push(const T &&value) {
    if (full()) {
      return false;
    }
    mData[mIndxIn++ & mMask] = value;
    return true;
  }

  inline bool push(const T &value) {
    if (full()) {
      return false;
    }
    mData[mIndxIn++ & mMask] = value;
    return true;
  }

  [[nodiscard]] inline std::optional<std::reference_wrapper<volatile const T>> fetch() const volatile {
    if (empty()) {
      return {};
    }
    return mData[mIndxOut & mMask];
  }

  [[nodiscard]] inline std::optional<std::reference_wrapper<const T>> fetch() const {
    if (empty()) {
      return {};
    }

    return mData[mIndxOut & mMask];
  }
  inline void pop() volatile {
    if (!empty()) {
      mIndxOut = mIndxOut + 1;
    }
  }
  inline void pop() {
    if (!empty()) {
      mIndxOut++;
    }
  }

  [[nodiscard]] inline std::optional<std::reference_wrapper<volatile const T>> pull() volatile {
    if (empty()) {
      return {};
    }

    mIndxOut = mIndxOut + 1;
    return mData[(mIndxOut - 1) & mMask];
  }

  [[nodiscard]] inline std::optional<std::reference_wrapper<const T>> pull() {
    if (empty()) {
      return {};
    }

    return mData[mIndxOut++ & mMask];
  }
};

} // namespace iso::buffer