#include "stm32f10x.h"

volatile uint32_t count_01Hz = 0;
volatile uint32_t count_1Hz  = 0;
volatile uint32_t count_10Hz = 0;


/*
 * SysTick chạy mỗi 1 ms
 *
 * HSI mặc định = 8 MHz
 * 8000000 / 1000 = 8000
 */
void SysTick_Handler(void)
{
    /* =========================
       LED PA0 = 0.1 Hz
       Toggle mỗi 5 giây
       ========================= */
    count_01Hz++;

    if (count_01Hz >= 5000)
    {
        GPIOA->ODR ^= (1 << 0);
        count_01Hz = 0;
    }


    /* =========================
       LED PA1 = 1 Hz
       Toggle mỗi 500 ms
       ========================= */
    count_1Hz++;

    if (count_1Hz >= 500)
    {
        GPIOA->ODR ^= (1 << 1);
        count_1Hz = 0;
    }


    /* =========================
       LED PA2 = 10 Hz
       Toggle mỗi 50 ms
       ========================= */
    count_10Hz++;

    if (count_10Hz >= 50)
    {
        GPIOA->ODR ^= (1 << 2);
        count_10Hz = 0;
    }
}


int main(void)
{
    /* =========================
       Bật clock GPIOA
       ========================= */
    RCC->APB2ENR |= (1 << 2);


    /* =========================
       PA0, PA1, PA2 OUTPUT
       Push-pull
       50 MHz

       PA0 -> LED 0.1 Hz
       PA1 -> LED 1 Hz
       PA2 -> LED 10 Hz
       ========================= */

    GPIOA->CRL &= ~(
        (0xF << 0) |
        (0xF << 4) |
        (0xF << 8)
    );

    GPIOA->CRL |= (
        (0x3 << 0) |
        (0x3 << 4) |
        (0x3 << 8)
    );


    /* LED ban đầu OFF */
    GPIOA->ODR &= ~(
        (1 << 0) |
        (1 << 1) |
        (1 << 2)
    );


    /* =========================
       Cấu hình SysTick

       HSI = 8 MHz

       8,000,000 / 1000
       = 8000 lần đếm / 1 ms
       ========================= */

    SysTick->LOAD = 8000 - 1;

    SysTick->VAL = 0;


    /*
       CTRL:

       bit 0 = 1 -> Enable SysTick
       bit 1 = 1 -> Enable interrupt
       bit 2 = 1 -> Clock = CPU clock
    */

    SysTick->CTRL = 7;


    /* =========================
       Main không cần delay
       SysTick tự động gọi
       SysTick_Handler() mỗi 1 ms
       ========================= */

    while (1)
    {
    }
}
