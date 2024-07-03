//Where is the LED connected?
//Port: G
//Pin: 13

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE  	(PERIPH_BASE + AHB1PERIPH_OFFSET) //0x4002 0000
#define GPIOG_OFFSET		(0x00001800UL)
#define GPIOG_BASE          	(AHB1PERIPH_BASE + GPIOG_OFFSET)

#define RCC_OFFSET 		(0x3800UL)
#define RCC_BASE		(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1ENR_R_OFFSET	(0x30UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1ENR_R_OFFSET))

#define MODE_R_OFFSET		(0x00UL)
#define GPIOG_MODE_R		(*(volatile unsigned int *)(GPIOG_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET		(0x14UL)
#define GPIOG_OD_R 		(*(volatile unsigned int *)(GPIOG_BASE + OD_R_OFFSET))

// Shift one to position six. Note: one replaces the sixth position of zero
#define GPIOGEN			(1U<<6) // 0b 0000 0000 0000 0000 0000 0000 0100 0000

#define PIN13 			(1U<<13)
#define LED_PIN			PIN13	

/*
 * (1U<<26) // Set bit 26 to 1
 * &=~(1U<<27) // Set only bit 27 to 0
 */

/*
 * rcc_ahb1enr reg = 0b 0000 0000 0000 0000 0000 0000 0100 0000
 */

int main(void)
{
	/*1. Enable clock access to GPIOG */
	RCC_AHB1EN_R |= GPIOGEN;

	/*2. Set PG13 as output pin */
	GPIOG_MODE_R |= (1U<<26); // Set bit 26 to 1
	GPIOG_MODE_R &=~(1U<<27); // Set only bit 27 to 0

	while(1)
	{
		/*3. Set PG13 High */
		//GPIOG_OD_R |= LED_PIN;

		/*4. Experiment 2: toggle PG13 */
		GPIOG_OD_R ^= LED_PIN;
		for (int i=0; i < 100000; i++) {}

	}
}
