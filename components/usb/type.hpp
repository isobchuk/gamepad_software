#pragma once

#include <bit>
#include <concepts>
#include <cstdint>

namespace iso::usb {
namespace Type {
using Byte = uint8_t;
using Word = uint16_t;
using Index = uint8_t;
using Bcd = uint16_t;
using Id = uint16_t;
template <typename Type> using BitMap = Type;
}; // namespace Type

/*class architecture final {
  architecture() = delete;

  template <const std::endian end> inline static constexpr bool _check_endian = (end == std::endian::native);

public:
  template <std::unsigned_integral T> inline static T cast(T val) { return val; }

  template <std::unsigned_integral T>
  requires _check_endian<std::endian::big>
  inline static T cast(T val) {
    if constexpr (sizeof(Type::Byte) == sizeof(T)) {
      return val;
    } else if (sizeof(Type::Word) == sizeof(T)) {
      return ((val & 0xFFU) << 8) | ((val & 0xFF00) >> 8);
    } else {
      static_assert((sizeof(Type::Word) < sizeof(T)), "The maximum type size is Type::Word");
    }
  }

// template <std::same_as<Type::Byte> First, std::same_as<Type::Byte>... Rest> inline static T cast(const First first, const Rest...rest) { return
// val; }

// template <const size_t N> static consteval size_t size(const Type::Byte (&)[N]) { return N; }
};*/

} // namespace iso::usb