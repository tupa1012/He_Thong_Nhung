#include "stm32f10x.h"
#include "timer.h"
#include "uart.h"

static int string_equal(char *a, char *b)
{
    while (*a && *b)
    {
        if (*a != *b)
            return 0;

        a++;
        b++;
    }

    return (*a == '\0' && *b == '\0');
}

static int string_start(char *s, char *prefix)
{
    while (*prefix)
    {
        if (*s != *prefix)
            return 0;

        s++;
        prefix++;
    }

    return 1;
}

static uint8_t get_percent(char *s)
{
    uint8_t value = 0;

    while (*s >= '0' && *s <= '9')
    {
        value = value * 10 + (*s - '0');
        s++;
    }

    return value;
}

static void process_command(char *cmd)
{
    uint8_t percent;

    /* ON! */
    if (string_equal(cmd, "ON"))
    {
        PWM_On();

        UART_SendString("LED ON\r\n");
    }

    /* OFF! */
    else if (string_equal(cmd, "OFF"))
    {
        PWM_Off();

        UART_SendString("LED OFF\r\n");
    }

    /* PWM:Percent! */
    else if (string_start(cmd, "PWM:"))
    {
        percent = get_percent(cmd + 4);

        if (percent <= 100)
        {
            PWM_SetDuty(percent);

            UART_SendString("PWM = ");
            UART_SendNumber(percent);
            UART_SendString("%\r\n");
        }
        else
        {
            UART_SendString("ERROR\r\n");
        }
    }

    /* Status! */
    else if (string_equal(cmd, "Status"))
    {
        UART_SendString("STATUS: ");

        if (PWM_GetState())
            UART_SendString("ON");
        else
            UART_SendString("OFF");

        UART_SendString(" | PWM = ");

        UART_SendNumber(PWM_GetDuty());

        UART_SendString("%\r\n");
    }

    else
    {
        UART_SendString("UNKNOWN COMMAND\r\n");
    }
}

int main(void)
{
    char cmd[32];

    /* Khởi tạo PWM */
    Timer_PWM_Init();

    /* Khởi tạo UART + interrupt */
    UART_Init();

    UART_SendString("STM32 PWM UART READY\r\n");

    while (1)
    {
        if (UART_CommandReady())
        {
            UART_GetCommand(cmd);

            process_command(cmd);
        }
    }
}
