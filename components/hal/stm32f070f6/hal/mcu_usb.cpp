#include "mcu_usb.hpp"

namespace stm32f0x0::usb {
volatile Usb::SControlEndpoint Usb::sControlEndpointReceiveBuffer(0U, iso::usb::endpoint::EDirection::Out);
}