#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOGEN				(1U<<6) // 0b 0000 0000 0000 0000 0000 0000 0100 0000

#define PIN13 				(1U<<13)
#define LED_PIN				PIN13


char key;

int main(void)
{
	/*1. Enable clock access to GPIOG */
	RCC->AHB1ENR |= GPIOGEN;

	/*2. Set PG13 as output pin */
	GPIOG->MODER |= (1U<<26); // Set bit 26 to 1
	GPIOG->MODER &=~(1U<<27); // Set only bit 27 to 0

    uart1_rxtx_init(); /* Initialized our rxtx */

    while (1)
    {
        key = uart1_read();
        if (key == '1')
        {
        	GPIOG->ODR |= LED_PIN;
        }
        else
        {
        	GPIOG->ODR &= ~LED_PIN;
        }
    }
}
