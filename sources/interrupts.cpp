#include "config.hpp"

using namespace gamepad;

void SysTick_Handler(void) { processor::systemTimer.InterruptHandler(); }

void USB_IRQHandler() { integrationUsb._Hardware.InterruptHandler(); }