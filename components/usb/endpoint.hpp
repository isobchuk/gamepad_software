#pragma once

#include "type.hpp"

namespace iso::usb::endpoint {

enum class EDirection : Type::Byte { Out, In };

template <typename T>
concept cArray = std::is_array_v<T>;

template <typename T>
concept c_endpoint = requires(T ep) {
  { (decltype(ep.aBuffer)){} } -> std::same_as<Type::Byte(&)[T::_BUFFER_SIZE]>;
  { (decltype(ep.sLength)){} } -> std::unsigned_integral;
  { (const decltype(ep.bNumber)){} } -> std::same_as<unsigned>;
  { (const decltype(ep.bDirection)){} } -> std::same_as<EDirection>;
};

template <const unsigned sz> class CEndpoint final {
private:
  using size_t = decltype(sz);
  static constexpr auto _BUFFER_SIZE = sz;

public:
  Type::Byte aBuffer[_BUFFER_SIZE];
  unsigned sLength;
  const unsigned bNumber;
  const EDirection bDirection;

  inline CEndpoint(const unsigned num, const EDirection dir)
  requires c_endpoint<CEndpoint>
      : sLength(0), bNumber(num), bDirection(dir) {}

  inline operator bool() volatile const { return 0 == sLength; }
};

} // namespace iso::usb::endpoint