#pragma once

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
} // namespace iso::usb