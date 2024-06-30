#include "button.hpp"
#include "config.hpp"
#include "device.hpp"
#include "integration_usb.hpp"

#include "meta_types.hpp"

using namespace gamepad;

using namespace iso::usb;
namespace gamepad {
class GameController final {
  static constexpr ::hardware::button::Button button0{processor::gpio[iso::meta_type::const_v<gamepad::PinFunction::Button0>],
                                                      iso::meta_type::const_v<true>};
  static constexpr ::hardware::button::Button button1{processor::gpio[iso::meta_type::const_v<gamepad::PinFunction::Button1>],
                                                      iso::meta_type::const_v<true>};
  static constexpr ::hardware::button::Button button2{processor::gpio[iso::meta_type::const_v<gamepad::PinFunction::Button2>],
                                                      iso::meta_type::const_v<true>};
  static constexpr ::hardware::button::Button button3{processor::gpio[iso::meta_type::const_v<gamepad::PinFunction::Button3>],
                                                      iso::meta_type::const_v<true>};

  static constexpr ::hardware::button::Button buttonLed{processor::gpio[iso::meta_type::const_v<gamepad::PinFunction::ButtonLed>],
                                                        iso::meta_type::const_v<true>};

  static constexpr mcu::adc::CAdc adc{iso::meta_type::const_v<mcu::adc::EAdcChannels::Number0>,
                                      iso::meta_type::const_v<mcu::adc::EAdcChannels::Number1>};

public:
  consteval GameController() = default;

  inline void Init() const { adc.Init(); }

  void Refresh() const {
    static Timeout timeoutGamepad;
    static Timeout timeoutLed;

    static bool buttonLedState;

    time.Start(timeoutGamepad);
    if (time.Check(timeoutGamepad, 25U)) {
      // static constexpr uint8_t reportId = 1;
      //  uint8_t buffer[] = {0, 0, 0, reportId};

      uint8_t buffer1[] = {0b0000, 0, 0, 0};

      if (button0.Read()) {
        buffer1[0] |= 1U << 0;
      }

      if (button1.Read()) {
        buffer1[0] |= 1U << 1;
      }

      if (button2.Read()) {
        buffer1[0] |= 1U << 2;
      }

      if (button3.Read()) {
        buffer1[0] |= 1U << 3;
      }

      if (buttonLed.Read()) {
        buffer1[0] |= 1U << 4;
      }

      if (buttonLed.Read() && !buttonLedState) {
        led.Change();
        buttonLedState = true;
      } else if (!buttonLed.Read() && buttonLedState) {
        buttonLedState = false;
      }

      uint8_t joystick[2] = {0, 0};
      adc.Value(joystick);

      buffer1[1] = joystick[1];
      buffer1[2] = joystick[0];

      // integrationUsb.Refresh(buffer);
      integrationUsb.Refresh(buffer1);
    }
  }
};
} // namespace gamepad

int main() {

  static constexpr auto usbDevice = UsbDevice(integrationUsb);
  static constexpr GameController controller{};

  processor::interrupt.GlobalEnable();
  processor::clock.Init();
  processor::gpio.Init();
  processor::systemTimer.Init();

  usbDevice.Init();
  gamepad::processor::interrupt[iso::meta_type::const_v<stm32f0x0::interrupt::Number::USB>].Enable();

  controller.Init();

  while (true) {
    usbDevice();
    controller.Refresh();
  }
  return 0;
}
