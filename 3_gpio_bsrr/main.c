#include "stm32f4xx.h"

#define GPIOGEN		(1U<<6)
#define PIN13		(1U<<13)
#define LED_PIN 	PIN13


int main(void)
{
	RCC->AHB1ENR |= GPIOGEN;

	GPIOG->MODER |= (1U<<26);
	GPIOG->MODER &=~ (1U<<27);
	while(1)
	{
		GPIOG->BSRR = LED_PIN;
		for (int i = 0; i < 100000; i++){}

		GPIOG->BSRR = (1U<<29);
		for (int i = 0; i < 100000; i++){}
	}
}
