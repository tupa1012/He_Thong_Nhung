.syntax unified
.cpu cortex-m3
.thumb

.global Reset_Handler
.global _estack

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
    .word Reset_Handler       /* Reset */
    .word Default_Handler     /* NMI */
    .word Default_Handler     /* HardFault */
    .word Default_Handler     /* MemManage */
    .word Default_Handler     /* BusFault */
    .word Default_Handler     /* UsageFault */
    .word 0                   /* Reserved */
    .word 0                   /* Reserved */
    .word 0                   /* Reserved */
    .word 0                   /* Reserved */
    .word Default_Handler     /* SVCall */
    .word Default_Handler     /* DebugMonitor */
    .word 0                   /* Reserved */
    .word Default_Handler     /* PendSV */
    .word Default_Handler     /* SysTick */


    /* =========================
       STM32F103 Interrupts
       ========================= */

    .word Default_Handler     /* WWDG */
    .word Default_Handler     /* PVD */
    .word Default_Handler     /* TAMPER */
    .word Default_Handler     /* RTC */
    .word Default_Handler     /* FLASH */
    .word Default_Handler     /* RCC */
    .word Default_Handler     /* EXTI0 */
    .word Default_Handler     /* EXTI1 */
    .word Default_Handler     /* EXTI2 */
    .word Default_Handler     /* EXTI3 */
    .word Default_Handler     /* EXTI4 */
    .word Default_Handler     /* DMA1_Channel1 */
    .word Default_Handler     /* DMA1_Channel2 */
    .word Default_Handler     /* DMA1_Channel3 */
    .word Default_Handler     /* DMA1_Channel4 */
    .word Default_Handler     /* DMA1_Channel5 */
    .word Default_Handler     /* DMA1_Channel6 */
    .word Default_Handler     /* DMA1_Channel7 */
    .word Default_Handler     /* ADC1_2 */
    .word Default_Handler     /* USB_HP_CAN_TX */
    .word Default_Handler     /* USB_LP_CAN_RX0 */
    .word Default_Handler     /* CAN_RX1 */
    .word Default_Handler     /* CAN_SCE */
    .word Default_Handler     /* EXTI9_5 */
    .word Default_Handler     /* TIM1_BRK */
    .word Default_Handler     /* TIM1_UP */
    .word Default_Handler     /* TIM1_TRG_COM */
    .word Default_Handler     /* TIM1_CC */
    .word Default_Handler     /* TIM2 */
    .word Default_Handler     /* TIM3 */
    .word Default_Handler     /* TIM4 */
    .word Default_Handler     /* I2C1_EV */
    .word Default_Handler     /* I2C1_ER */
    .word Default_Handler     /* I2C2_EV */
    .word Default_Handler     /* I2C2_ER */
    .word Default_Handler     /* SPI1 */
    .word Default_Handler     /* SPI2 */
    .word Default_Handler     /* USART1 */
    .word Default_Handler     /* USART2 */
    .word Default_Handler     /* USART3 */
    .word Default_Handler     /* EXTI15_10 */
    .word Default_Handler     /* RTCAlarm */
    .word Default_Handler     /* USBWakeUp */


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
