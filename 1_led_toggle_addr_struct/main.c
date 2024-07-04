//Where is the LED connected?
//Port: G
//Pin: 13
#include <stdint.h>

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE  	(PERIPH_BASE + AHB1PERIPH_OFFSET) //0x4002 0000
#define GPIOG_OFFSET		(0x00001800UL)
#define GPIOG_BASE          (AHB1PERIPH_BASE + GPIOG_OFFSET)

#define RCC_OFFSET 			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)


// Shift one to position sixth. Note: one replaces the sixth position of zero
#define GPIOGEN				(1U<<6) // 0b 0000 0000 0000 0000 0000 0000 0100 0000

#define PIN13 				(1U<<13)
#define LED_PIN				PIN13

#define __IO volatile

typedef struct
{

	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;		/*!< RCC AHB1 peripheral clock register			Address offset: 0x30 */

}RCC_TypeDef;

typedef struct
{
	volatile uint32_t MODER; 	/*!< GPIO port mode register, 				        Address offset: 0x00		*/
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;		/*!< GPIO port output data register,		        Address offset: 0x14		*/
}GPIO_TypeDef;



#define RCC 	((RCC_TypeDef*) RCC_BASE)
#define GPIOG 	((GPIO_TypeDef*)GPIOG_BASE)



int main(void)
{
	/*1. Enable clock access to GPIOG */
	RCC->AHB1ENR |= GPIOGEN;

	/*2. Set PG13 as output pin */
	GPIOG->MODER |= (1U<<26); // Set bit 26 to 1
	GPIOG->MODER &=~(1U<<27); // Set only bit 27 to 0

	while(1)
	{
		GPIOG->ODR ^= LED_PIN;
		for (int i=0; i < 100000; i++) {}

	}
}
