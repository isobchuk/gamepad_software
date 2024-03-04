#pragma once

#include "meta_types.hpp"
#include "reg_gpio.hpp"
#include <concepts>

namespace stm32f0x0::hal::gpio {

enum class Port { PA, PB };
enum class Pin { Pin_0, Pin_1, Pin_2, Pin_3, Pin_4, Pin_5, Pin_6, Pin_7, Pin_8, Pin_9, Pin_10, Pin_11, Pin_12, Pin_13, Pin_14, Pin_15 };
enum class Mode : uint32_t { Input, Output, Alternate, Analog };
enum class Type : uint32_t { PushPull, OpenDrain };
enum class Speed : uint32_t { Low, Medium, High = 0b11 };
enum class Pull : uint32_t { None, Up, Down };
enum class Alternative : uint32_t { AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7 };

struct PinConfig {
  const Type cm_Type;
  const Speed cm_Speed;
  const Pull cm_Pull;
  const Alternative cm_AlternativeFunction;

  template <typename... AddParams>
  requires iso::meta_type::var_pack::is_types_unique_v<AddParams...> &&
               iso::meta_type::var_pack::is_type_list<Type, Speed, Pull, Alternative>::contains_v<AddParams...>
  consteval PinConfig(const AddParams... p_AddParams)
      : cm_Type(iso::meta_type::var_pack::type<Type>::get(p_AddParams...)), cm_Speed(iso::meta_type::var_pack::type<Speed>::get(p_AddParams...)),
        cm_Pull(iso::meta_type::var_pack::type<Pull>::get(p_AddParams...)),
        cm_AlternativeFunction(iso::meta_type::var_pack::type<Alternative>::get(p_AddParams...)) {}
};

template <typename T>
concept pin_function = std::is_enum_v<T>;

template <pin_function Function> struct PinOut {
  const Function cm_Function;
  const Port cm_Port;
  const Pin cm_Pin;
  const Mode cm_Mode;
  const PinConfig cm_Config;

  consteval PinOut(const Function func, const Port port, const Pin pin, const Mode mode, const PinConfig config)
      : cm_Function(func), cm_Port(port), cm_Pin(pin), cm_Mode(mode), cm_Config(config) {}
};

template <const Port port, const Pin pin, const Mode mode> class Gpio final {
  static constexpr stm32f0x0::gpio::GPIO_T<0x48000000UL + (0x400UL * static_cast<uint32_t>(port))> *PORT{};
  static constexpr auto PIN = cpp_register::reg_v<1UL, static_cast<uint32_t>(pin)>;
  static constexpr auto MODE = mode;

public:
  consteval Gpio() = default;

  template <iso::meta_type::const_value State>
  inline void Write(const State) const
  requires((Mode::Output == MODE) && std::same_as<bool, typename State::type>)
  {
    using namespace stm32f0x0::gpio;
    if constexpr (State::value) {
      PORT->BSRR = GPIO_BSRR::BS[PIN];
    } else {
      PORT->BSRR = GPIO_BSRR::BR[PIN];
    }
  }

  inline bool Read() const
  requires(Mode::Input == MODE)
  {
    using namespace stm32f0x0::gpio;
    return (PORT->IDR & GPIO_IDR::IDR[PIN]);
  }

  inline void Change() const
  requires(Mode::Output == MODE)
  {
    using namespace stm32f0x0::gpio;
    PORT->ODR ^= GPIO_ODR::ODR[PIN];
  }
};

template <const auto &table> class GpioController final {
  static constexpr auto &cm_GpioTable = table;
  using PinFunction = decltype(cm_GpioTable[0].cm_Function);

  static consteval unsigned GetIndexByPinFunction(const PinFunction func) {
    unsigned index = 0;
    while (func != cm_GpioTable[index].cm_Function) {
      index++;
    }
    return index;
  }

  template <const Port port, const unsigned step = 0> static consteval auto GetMode() {
    using namespace stm32f0x0::gpio;
    using namespace cpp_register;

    if constexpr ((sizeof(cm_GpioTable) / sizeof(cm_GpioTable[0])) == step + 1) {
      if constexpr (cm_GpioTable[step].cm_Port != port) {
        return GPIO_MODER::MODER[constants::ZERO](constants::ZERO);
      } else {
        return GPIO_MODER::MODER[reg_v<1UL, static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)>](reg_v<cm_GpioTable[step].cm_Mode>);
      }
    } else {
      if constexpr (cm_GpioTable[step].cm_Port != port) {
        return GetMode<port, step + 1>();
      } else {
        return GPIO_MODER::MODER[reg_v<1UL, static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)>](reg_v<cm_GpioTable[step].cm_Mode>) |
               GetMode<port, step + 1>();
      }
    }
  }

  template <const Port port, const unsigned step = 0> static consteval auto GetType() {
    using namespace stm32f0x0::gpio;
    using namespace cpp_register;

    if constexpr ((sizeof(cm_GpioTable) / sizeof(cm_GpioTable[0])) == step + 1) {
      if constexpr (cm_GpioTable[step].cm_Port != port) {
        return GPIO_OTYPER::OT[constants::ZERO](constants::ZERO);
      } else {
        return GPIO_OTYPER::OT[reg_v<1UL, static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)>](reg_v<cm_GpioTable[step].cm_Config.cm_Type>);
      }
    } else {
      if constexpr (cm_GpioTable[step].cm_Port != port) {
        return GetType<port, step + 1>();
      } else {
        return GPIO_OTYPER::OT[reg_v<1UL, static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)>](reg_v<cm_GpioTable[step].cm_Config.cm_Type>) |
               GetType<port, step + 1>();
      }
    }
  }

  template <const Port port, const unsigned step = 0> static consteval auto GetSpeed() {
    using namespace stm32f0x0::gpio;
    using namespace cpp_register;

    if constexpr ((sizeof(cm_GpioTable) / sizeof(cm_GpioTable[0])) == step + 1) {
      if constexpr (cm_GpioTable[step].cm_Port != port) {
        return GPIO_OSPEEDR::OSPEEDR[constants::ZERO](constants::ZERO);
      } else {
        return GPIO_OSPEEDR::OSPEEDR[reg_v<1UL, static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)>](reg_v<cm_GpioTable[step].cm_Config.cm_Speed>);
      }
    } else {
      if constexpr (cm_GpioTable[step].cm_Port != port) {
        return GetSpeed<port, step + 1>();
      } else {
        return GPIO_OSPEEDR::OSPEEDR[reg_v<1UL, static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)>](reg_v<cm_GpioTable[step].cm_Config.cm_Speed>) |
               GetSpeed<port, step + 1>();
      }
    }
  }

  template <const Port port, const unsigned step = 0> static consteval auto GetPull() {
    using namespace stm32f0x0::gpio;
    using namespace cpp_register;

    if constexpr ((sizeof(cm_GpioTable) / sizeof(cm_GpioTable[0])) == step + 1) {
      if constexpr (cm_GpioTable[step].cm_Port != port) {
        return GPIO_PUPDR::PUPDR[constants::ZERO](constants::ZERO);
      } else {
        return GPIO_PUPDR::PUPDR[reg_v<1UL, static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)>](reg_v<cm_GpioTable[step].cm_Config.cm_Pull>);
      }
    } else {
      if constexpr (cm_GpioTable[step].cm_Port != port) {
        return GetPull<port, step + 1>();
      } else {
        return GPIO_PUPDR::PUPDR[reg_v<1UL, static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)>](reg_v<cm_GpioTable[step].cm_Config.cm_Pull>) |
               GetPull<port, step + 1>();
      }
    }
  }

  enum class AlFunctRegGrade : unsigned { Junior, Senior };

  template <const Port port, const AlFunctRegGrade grade, const unsigned step = 0> static consteval auto GetAlternativeFunction() {
    using namespace stm32f0x0::gpio;
    using namespace cpp_register;

    if constexpr ((sizeof(cm_GpioTable) / sizeof(cm_GpioTable[0])) == step + 1) {
      if constexpr ((cm_GpioTable[step].cm_Port != port) || ((AlFunctRegGrade::Junior == grade) && (cm_GpioTable[step].cm_Pin) > Pin::Pin_7) ||
                    ((AlFunctRegGrade::Senior == grade) && (cm_GpioTable[step].cm_Pin <= Pin::Pin_7))) {
        return GPIO_AFR::AFR[constants::ZERO](constants::ZERO);
      } else {
        constexpr auto pinNum = ((AlFunctRegGrade::Junior == grade) ? static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)
                                                                    : static_cast<uint8_t>(cm_GpioTable[step].cm_Pin) - 8);
        return GPIO_AFR::AFR[reg_v<1UL, pinNum>](reg_v<cm_GpioTable[step].cm_Config.cm_AlternativeFunction>);
      }
    } else {
      if constexpr ((cm_GpioTable[step].cm_Port != port) || ((AlFunctRegGrade::Junior == grade) && (cm_GpioTable[step].cm_Pin) > Pin::Pin_7) ||
                    ((AlFunctRegGrade::Senior == grade) && (cm_GpioTable[step].cm_Pin) <= Pin::Pin_7)) {
        return GetAlternativeFunction<port, grade, step + 1>();
      } else {
        constexpr auto pinNum = ((AlFunctRegGrade::Junior == grade) ? static_cast<uint8_t>(cm_GpioTable[step].cm_Pin)
                                                                    : static_cast<uint8_t>(cm_GpioTable[step].cm_Pin) - 8);
        return GPIO_AFR::AFR[reg_v<1UL, pinNum>](reg_v<cm_GpioTable[step].cm_Config.cm_AlternativeFunction>) |
               GetAlternativeFunction<port, grade, step + 1>();
      }
    }
  }

public:
  consteval GpioController() = default;

  void Init() const {
    using namespace stm32f0x0::gpio;
    using namespace cpp_register;

    constexpr auto modeA = GetMode<Port::PA>();
    constexpr auto modeB = GetMode<Port::PB>();

    if constexpr (modeA.sc_Value) {
      GPIOA->MODER |= modeA;
    }

    if constexpr (modeB.sc_Value) {
      GPIOB->MODER |= modeB;
    }

    constexpr auto typeA = GetType<Port::PA>();
    constexpr auto typeB = GetType<Port::PB>();

    if constexpr (typeA.sc_Value) {
      GPIOA->OTYPER |= typeA;
    }

    if constexpr (typeB.sc_Value) {
      GPIOB->OTYPER |= typeB;
    }

    constexpr auto speedA = GetSpeed<Port::PA>();
    constexpr auto speedB = GetSpeed<Port::PB>();

    if constexpr (speedA.sc_Value) {
      GPIOA->OSPEEDR |= speedA;
    }

    if constexpr (speedB.sc_Value) {
      GPIOB->OSPEEDR |= speedB;
    }

    constexpr auto pullA = GetPull<Port::PA>();
    constexpr auto pullB = GetPull<Port::PB>();

    if constexpr (pullA.sc_Value) {
      GPIOA->PUPDR |= pullA;
    }

    if constexpr (pullB.sc_Value) {
      GPIOB->PUPDR |= pullB;
    }

    constexpr auto afJrA = GetAlternativeFunction<Port::PA, AlFunctRegGrade::Junior>();
    constexpr auto afSrA = GetAlternativeFunction<Port::PA, AlFunctRegGrade::Senior>();
    constexpr auto afJrB = GetAlternativeFunction<Port::PB, AlFunctRegGrade::Junior>();
    constexpr auto afSrB = GetAlternativeFunction<Port::PB, AlFunctRegGrade::Senior>();

    if constexpr (afJrA.sc_Value) {
      GPIOA->AFR[reg_v<0UL>] |= afJrA;
    }

    if constexpr (afSrA.sc_Value) {
      GPIOA->AFR[reg_v<1UL>] |= afSrA;
    }

    if constexpr (afJrB.sc_Value) {
      GPIOB->AFR[reg_v<0UL>] |= afJrB;
    }

    if constexpr (afSrB.sc_Value) {
      GPIOB->AFR[reg_v<1UL>] |= afSrB;
    }
  }

  template <iso::meta_type::const_value Function>
  requires std::same_as<PinFunction, const typename Function::type>
  [[nodiscard]] inline consteval auto operator[](const Function) const {
    constexpr auto index = GetIndexByPinFunction(Function::value);
    return Gpio<cm_GpioTable[index].cm_Port, cm_GpioTable[index].cm_Pin, cm_GpioTable[index].cm_Mode>{};
  }
};

} // namespace stm32f0x0::hal::gpio