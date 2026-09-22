#include "adc.h"

void ADC_Init(void)
{
    /* Bật clock GPIOA + ADC1 */
    RCC->APB2ENR |= (1 << 2) | (1 << 9);

    /* PA0 = Analog input */
    GPIOA->CRL &= ~(0xF << 0);

    /* ADC clock = PCLK2 / 2 = 4 MHz */
    RCC->CFGR &= ~(0x3 << 14);

    /* Channel 0, sample time = 239.5 cycles */
    ADC1->SMPR2 |= (0x7 << 0);

    /* Software trigger */
    ADC1->CR2 |= (0x7 << 17);
    ADC1->CR2 |= (1 << 20);

    /* ADC ON */
    ADC1->CR2 |= (1 << 0);

    /* Reset calibration */
    ADC1->CR2 |= (1 << 3);
    while (ADC1->CR2 & (1 << 3));

    /* Calibration */
    ADC1->CR2 |= (1 << 2);
    while (ADC1->CR2 & (1 << 2));
}

uint16_t ADC_Read(void)
{
    /* Start conversion */
    ADC1->CR2 |= (1 << 22);

    /* Chờ conversion xong */
    while (!(ADC1->SR & (1 << 1)));

    return ADC1->DR;
}

uint16_t ADC_ReadVoltage(void)
{
    uint32_t adc;

    adc = ADC_Read();

    /* Vref = 3.3V */
    return (adc * 3300) / 4095;
}
