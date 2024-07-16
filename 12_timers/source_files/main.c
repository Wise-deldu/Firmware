#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOGEN			(1U<<6)

#define PIN13 			(1U<<13)
#define LED				PIN13

int main(void)
{
	RCC->AHB1ENR |= GPIOGEN;

	GPIOG->MODER |= (1U<<26);
	GPIOG->MODER &=~(1U<<27);


    uart1_tx_init();
    tim2_1hz_init(); /* Initialize our timer for 1Hz */

    while (1)
    {
    	/* Wait for UIF */
    	while (!(TIM2->SR & SR_UIF)){}

    	/* Clear UIF */
    	TIM2->SR &=~ SR_UIF;

    	printf("A second elapsed !! \n\r");
    	GPIOG->ODR ^= LED;

    }
}