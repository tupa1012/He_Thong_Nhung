#include "stm32f10x.h"
#include "uart.h"

/* =========================
   THAY THÔNG TIN CỦA BẠN
   ========================= */

#define MA_LOP  "DTMT2"
#define MA_NHOM "02"


int string_equal(char *a, char *b)
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


int main(void)
{
    char message[64];

    UART_Init();

    UART_SendString("UART READY\r\n");

    while (1)
    {
        if (UART_CommandReady())
        {
            UART_GetBuffer(message);

            /* <Ma lop><Ma nhom>: <Ban tin>\r\n */

            UART_SendString(MA_LOP);
            UART_SendString(MA_NHOM);
            UART_SendString(": ");

            UART_SendString(message);

            UART_SendString("\r\n");
        }
    }
}
