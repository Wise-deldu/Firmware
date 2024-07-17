#include "stm32f4xx.h"

#define TIM2EN      (1U<<0)
#define CR1_CEN     (1U<<0)
#define OC_TOGGLE   ((1U<<4) | (1U<<5))
#define CCER_CC1E   (1U<<0)

#define GPIOGEN     (1U<<6)
#define GPIOAEN		(1U<<0)
#define PIN13 		(1U<<13)
#define LED_PIN		PIN13

#define AFR5_TIM 	(1U<<20);

void tim2_1hz_init(void)
{
    /* Enable clock access to TIM2 */
    RCC->APB1ENR |= TIM2EN;

    /* Set prescaler value */
    TIM2->PSC = 1600 - 1; /* 16000000/1600 = 10000 */

    /* Set auto-reload value */
    TIM2->ARR = 10000 - 1; /* 10000/10000 = 1 */

    /* Clear counter */
    TIM2->CNT = 0;

    /* Enable timer */
    TIM2->CR1 = CR1_CEN;
}

void tim2_pa5_output_compare(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA5 mode to alternate function */
    GPIOA->MODER &=~ (1U<<27);
    GPIOA->MODER |=  (1U<<26);

    /* Set PA5 alternate function type to TIM2_CH1 (AF01) */
    GPIOA->AFR[0] |= AFR5_TIM;

    /* Enable clock access to TIM2 */
    RCC->APB1ENR |= TIM2EN;

    /* Set prescaler value */
    TIM2->PSC = 1600 - 1; /* 16000000/1600 = 10000 */

    /* Set auto-reload value */
    TIM2->ARR = 10000 - 1; /* 10000/10000 = 1 */

    /* Set output compare toggle mode */
    TIM2->CCMR1 = OC_TOGGLE;

    /* Enable TIM2_CH1 in compare mode */
    TIM2->CCER |= CCER_CC1E;

    /* Enable TIM2 interrupt in NVIC */
    TIM2->DIER |= (1U<<1); // CC1IE: Capture/Compare 1 interrupt enable
    NVIC_EnableIRQ(TIM2_IRQn);

    /* Clear counter */
    TIM2->CNT = 0;

    /* Enable timer */
    TIM2->CR1 = CR1_CEN;
}

void gpio_init(void)
{
	/*Enable clock access to GPIOG */
	RCC->AHB1ENR |= GPIOGEN;

	/* Set PG13 mode to output */
	GPIOG->MODER |= (1U<<26);
	GPIOG->MODER &=~ (1U<<27);
}

void TIM2_IRQHandler(void)
{
	/* Check if capture/compare interrupt flag is set */
	if (TIM2->SR & (1U<<1)) // CC1IF: Capture/Compare 1 interrupt flag
	{
		/* Clear capture/compare interrupt flag */
		TIM2->SR &=~ (1U<<1);

		/* Toggle the LED */
		GPIOG->ODR ^= LED_PIN;
	}
}