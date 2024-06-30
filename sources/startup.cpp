#include <cstdint>

int main();
extern "C" void Reset_Handler();
[[gnu::weak]] void NMI_Handler();
void HardFault_Handler();

void SVC_Handler();
void PendSV_Handler();
void SysTick_Handler();
void WWDG_IRQHandler();
void PVD_IRQHandler();
void RTC_IRQHandler();
void FLASH_IRQHandler();
void RCC_IRQHandler();
void EXTI0_1_IRQHandler();
void EXTI2_3_IRQHandler();
void EXTI4_15_IRQHandler();
void TS_IRQHandler();
void DMA1_Channel1_IRQHandler();
void DMA1_Channel2_3_IRQHandler();
void DMA1_Channel4_5_IRQHandler();
void ADC1_COMP_IRQHandler();
void TIM1_BRK_UP_TRG_COM_IRQHandler();
void TIM1_CC_IRQHandler();
void TIM2_IRQHandler();
void TIM3_IRQHandler();
void TIM6_DAC_IRQHandler();
void TIM14_IRQHandler();
void TIM15_IRQHandler();
void TIM16_IRQHandler();
void TIM17_IRQHandler();
void I2C1_IRQHandler();
void I2C2_IRQHandler();
void SPI1_IRQHandler();
void SPI2_IRQHandler();
void USART1_IRQHandler();
void USART2_IRQHandler();
void CEC_IRQHandler();
void USB_IRQHandler();
void BootRAM();

extern "C" void DefaultHandler();

#pragma weak NMI_Handler = DefaultHandler
#pragma weak SVC_Handler = DefaultHandler
#pragma weak PendSV_Handler = DefaultHandler
#pragma weak SysTick_Handler = DefaultHandler
#pragma weak WWDG_IRQHandler = DefaultHandler
#pragma weak PVD_IRQHandler = DefaultHandler
#pragma weak RTC_IRQHandler = DefaultHandler
#pragma weak FLASH_IRQHandler = DefaultHandler
#pragma weak RCC_IRQHandler = DefaultHandler
#pragma weak EXTI0_1_IRQHandler = DefaultHandler
#pragma weak EXTI2_3_IRQHandler = DefaultHandler
#pragma weak EXTI4_15_IRQHandler = DefaultHandler
#pragma weak TS_IRQHandler = DefaultHandler
#pragma weak DMA1_Channel1_IRQHandler = DefaultHandler
#pragma weak DMA1_Channel2_3_IRQHandler = DefaultHandler
#pragma weak DMA1_Channel4_5_IRQHandler = DefaultHandler
#pragma weak ADC1_COMP_IRQHandler = DefaultHandler
#pragma weak TIM1_BRK_UP_TRG_COM_IRQHandler = DefaultHandler
#pragma weak TIM1_CC_IRQHandler = DefaultHandler
#pragma weak TIM2_IRQHandler = DefaultHandler
#pragma weak TIM3_IRQHandler = DefaultHandler
#pragma weak TIM6_DAC_IRQHandler = DefaultHandler
#pragma weak TIM14_IRQHandler = DefaultHandler
#pragma weak TIM15_IRQHandler = DefaultHandler
#pragma weak TIM16_IRQHandler = DefaultHandler
#pragma weak TIM17_IRQHandler = DefaultHandler
#pragma weak I2C1_IRQHandler = DefaultHandler
#pragma weak I2C2_IRQHandler = DefaultHandler
#pragma weak SPI1_IRQHandler = DefaultHandler
#pragma weak SPI2_IRQHandler = DefaultHandler
#pragma weak USART1_IRQHandler = DefaultHandler
#pragma weak USART2_IRQHandler = DefaultHandler
#pragma weak CEC_IRQHandler = DefaultHandler
#pragma weak USB_IRQHandler = DefaultHandler
#pragma weak BootRAM = DefaultHandler

[[gnu::used, gnu::section(".isr_vector")]] static constinit void (*const p_sc_InterruptVectorTable[])(void) = {

    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    SVC_Handler,
    nullptr,
    nullptr,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,
    PVD_IRQHandler,
    RTC_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_1_IRQHandler,
    EXTI2_3_IRQHandler,
    EXTI4_15_IRQHandler,
    TS_IRQHandler,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_3_IRQHandler,
    DMA1_Channel4_5_IRQHandler,
    ADC1_COMP_IRQHandler,
    TIM1_BRK_UP_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM6_DAC_IRQHandler,
    nullptr,
    TIM14_IRQHandler,
    TIM15_IRQHandler,
    TIM16_IRQHandler,
    TIM17_IRQHandler,
    I2C1_IRQHandler,
    I2C2_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    nullptr,
    CEC_IRQHandler,
    USB_IRQHandler,
    BootRAM};

void Reset_Handler() {
  extern const uint32_t sdata;
  extern const uint32_t edata;
  extern const uint32_t szero;
  extern const uint32_t ezero;
  extern const uint32_t efixed;
  extern const uint32_t init_array_start;
  extern const uint32_t init_array_end;

  // Initialize data section
  uint32_t *poolValues = const_cast<uint32_t *>(&efixed);
  uint32_t *poolMemory = const_cast<uint32_t *>(&sdata);

  while (poolMemory < &edata) {
    *(poolMemory++) = *(poolValues++);
  }

  // Initialize bss section
  poolMemory = const_cast<uint32_t *>(&szero);
  while (poolMemory < &ezero) {
    *(poolMemory++) = 0UL;
  }

  // Call static constructors
  poolMemory = const_cast<uint32_t *>(&init_array_start);
  while (poolMemory < &init_array_end) {
    reinterpret_cast<void (*)()>((*(poolMemory++)))();
  }

  main();
}

void HardFault_Handler() {
  /*struct {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
  } *stack_ptr;

  asm("TST lr, #4 \n"
      "ITE EQ \n"
      "MRSEQ %[ptr], MSP  \n"
      "MRSNE %[ptr], PSP  \n"
      : [ptr] "=r"(stack_ptr));*/

  while (true) {
    asm("NOP");
  }
}

extern "C" void DefaultHandler() {
  while (true) {
    asm("NOP");
  }
}

extern "C" {
void _close(void) {}
void _lseek(void) {}
void _read(void) {}
void _write(void) {}
}