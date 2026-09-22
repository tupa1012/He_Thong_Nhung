.syntax unified
.cpu cortex-m3
.thumb

.global Reset_Handler
.global _estack
.global SysTick_Handler

.extern main


/* =========================================================
   VECTOR TABLE
   ========================================================= */

.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object

g_pfnVectors:

    /* =========================
       Cortex-M3 Core Exceptions
       ========================= */

    .word _estack
    .word Reset_Handler       /* 1  Reset */
    .word Default_Handler     /* 2  NMI */
    .word Default_Handler     /* 3  HardFault */
    .word Default_Handler     /* 4  MemManage */
    .word Default_Handler     /* 5  BusFault */
    .word Default_Handler     /* 6  UsageFault */
    .word 0                   /* 7  Reserved */
    .word 0                   /* 8  Reserved */
    .word 0                   /* 9  Reserved */
    .word 0                   /* 10 Reserved */
    .word Default_Handler     /* 11 SVCall */
    .word Default_Handler     /* 12 DebugMonitor */
    .word 0                   /* 13 Reserved */
    .word Default_Handler     /* 14 PendSV */

    /*
       QUAN TRỌNG:
       SysTick phải trỏ tới SysTick_Handler
    */
    .word SysTick_Handler     /* 15 SysTick */


    /* =========================
       STM32F103 Interrupts
       ========================= */

    .word Default_Handler     /* 16 WWDG */
    .word Default_Handler     /* 17 PVD */
    .word Default_Handler     /* 18 TAMPER */
    .word Default_Handler     /* 19 RTC */
    .word Default_Handler     /* 20 FLASH */
    .word Default_Handler     /* 21 RCC */
    .word Default_Handler     /* 22 EXTI0 */
    .word Default_Handler     /* 23 EXTI1 */
    .word Default_Handler     /* 24 EXTI2 */
    .word Default_Handler     /* 25 EXTI3 */
    .word Default_Handler     /* 26 EXTI4 */
    .word Default_Handler     /* 27 DMA1_Channel1 */
    .word Default_Handler     /* 28 DMA1_Channel2 */
    .word Default_Handler     /* 29 DMA1_Channel3 */
    .word Default_Handler     /* 30 DMA1_Channel4 */
    .word Default_Handler     /* 31 DMA1_Channel5 */
    .word Default_Handler     /* 32 DMA1_Channel6 */
    .word Default_Handler     /* 33 DMA1_Channel7 */
    .word Default_Handler     /* 34 ADC1_2 */
    .word Default_Handler     /* 35 USB_HP_CAN_TX */
    .word Default_Handler     /* 36 USB_LP_CAN_RX0 */
    .word Default_Handler     /* 37 CAN_RX1 */
    .word Default_Handler     /* 38 CAN_SCE */
    .word Default_Handler     /* 39 EXTI9_5 */
    .word Default_Handler     /* 40 TIM1_BRK */
    .word Default_Handler     /* 41 TIM1_UP */
    .word Default_Handler     /* 42 TIM1_TRG_COM */
    .word Default_Handler     /* 43 TIM1_CC */
    .word Default_Handler     /* 44 TIM2 */
    .word Default_Handler     /* 45 TIM3 */
    .word Default_Handler     /* 46 TIM4 */
    .word Default_Handler     /* 47 I2C1_EV */
    .word Default_Handler     /* 48 I2C1_ER */
    .word Default_Handler     /* 49 I2C2_EV */
    .word Default_Handler     /* 50 I2C2_ER */
    .word Default_Handler     /* 51 SPI1 */
    .word Default_Handler     /* 52 SPI2 */
    .word Default_Handler     /* 53 USART1 */
    .word Default_Handler     /* 54 USART2 */
    .word Default_Handler     /* 55 USART3 */
    .word Default_Handler     /* 56 EXTI15_10 */
    .word Default_Handler     /* 57 RTCAlarm */
    .word Default_Handler     /* 58 USBWakeUp */


/* =========================================================
   Reset Handler
   ========================================================= */

.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:

    /* Gọi main() */
    bl main

1:
    /* Nếu main return thì đứng đây */
    b 1b

.size Reset_Handler, . - Reset_Handler


/* =========================================================
   Default Handler
   ========================================================= */

.section .text.Default_Handler
.type Default_Handler, %function

Default_Handler:

1:
    b 1b

.size Default_Handler, . - Default_Handler
