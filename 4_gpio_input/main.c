#include "stm32f4xx.h"

#define GPIOGEN		(1U<<6)
#define GPIOAEN		(1U<<0)

#define PIN13		(1U<<13)
#define PIN0 		(1U<<0)

#define LED_PIN 	PIN13
#define BTN_PIN		PIN0


int main(void)
{
	/*Enable clock access to GPIOG and GPIOA */
	RCC->AHB1ENR |= GPIOGEN;
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PG13 as output pin */
	GPIOG->MODER |= (1U<<26);
	GPIOG->MODER &=~ (1U<<27);

	/*Set PA0 as input pin */
	GPIOA->MODER &=~ (1U<<0);
	GPIOA->MODER &=~ (1U<<1);

	while(1)
	{
		/*Check if BTN is pressed */
		if (GPIOA->IDR & BTN_PIN)
		{
			/*Turn on LED */
			GPIOG->BSRR = LED_PIN;
		}
		else
		{
			/*Turn of LED */
			GPIOG->BSRR = (1U<<29);
		}

	}
}
