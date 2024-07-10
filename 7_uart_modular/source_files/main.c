#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"




int main(void)
{
    uart1_tx_init(); /* Initialized the tx */

    while (1)
    {
        printf("Hello from STM32F4........\n\r");
    }
}