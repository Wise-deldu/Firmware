#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIOGEN			(1U<<6)

#define PIN13 			(1U<<13)
#define LED				PIN13

int main(void)
{
	RCC->AHB1ENR |= GPIOGEN;

	GPIOG->MODER |= (1U<<26);
	GPIOG->MODER &=~(1U<<27);


    uart1_tx_init();

    while (1)
    {
    	printf("A second passed !! \n\r");
    	GPIOG->ODR ^= LED;
    	systickDelayMs(1000);
    }
}