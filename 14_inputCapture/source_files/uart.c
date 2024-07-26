#include "uart.h"

#define GPIOAEN  (1U<<0)    // Enable clock for GPIOA
#define UART1EN  (1U<<4)    // Enable clock for USART1

#define CR1_TE   (1U<<3)
#define CR1_RE	 (1U<<2)

#define CR1_UE   (1U<<13)
#define SR_TXE   (1U<<7)
#define SR_RXNE  (1U<<5)

#define SYS_FREQ 16000000
#define APB2_CLK SYS_FREQ

#define UART_BAUDRATE  115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);



int __io_putchar(int ch)
{
	uart1_write(ch);
	return ch;
}

void uart1_rxtx_init(void)
{
    /************** Configure uart gpio pin ********************/
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA9 mode to alternate function mode (AF7) */
    GPIOA->MODER &= ~(1U << 18);  // Clear MODER9[1:0]
    GPIOA->MODER |=  (1U << 19);  // Set MODER9 to 10 (AF mode)

    /* Set PA9 alternate function type to UART_TX (AF7) */
    GPIOA->AFR[1] &= ~(0xF << 4); // Clear AFRH9[3:0]
    GPIOA->AFR[1] |=  (7 << 4);   // Set AFRH9 to AF7 (UART1 TX)

    /* Set PA10 mode to alternate function mode (AF7) */
    GPIOA->MODER &= ~(1U << 20);  // Clear MODER10[1:0]
    GPIOA->MODER |=  (1U << 21);  // Set MODER10 to 10 (AF mode)

    /* Set PA10 alternate function type to UART_RX (AF7) */
    GPIOA->AFR[1] |=  (1U<<8);  /* Set bit 8 */
    GPIOA->AFR[1] |=  (1U<<9);  /* Set bit 9 */
    GPIOA->AFR[1] |=  (1U<<10); /* Set bit 10 */
    GPIOA->AFR[1] &= ~(1U<<11); /* Reset or disable bit 11 */

    /************** Configure uart module ********************/
    /* Enable clock access to uart1 */
    RCC->APB2ENR |= UART1EN;

    /* Configure baudrate */
    uart_set_baudrate(USART1, APB2_CLK, UART_BAUDRATE);

    /* Configure the transfer direction */
    USART1->CR1 = (CR1_TE | CR1_RE);

    /* Enable uart module */
    USART1->CR1 |= CR1_UE;
}


void uart1_tx_init(void)
{
    /************** Configure uart gpio pin ********************/
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA9 mode to alternate function mode (AF7) */
    GPIOA->MODER &= ~(1U << 18);  // Clear MODER9[1:0]
    GPIOA->MODER |=  (1U << 19);  // Set MODER9 to 10 (AF mode)

    /* Set PA9 alternate function type to UART_TX (AF7) */
    GPIOA->AFR[1] &= ~(0xF << 4); // Clear AFRH9[3:0]
    GPIOA->AFR[1] |=  (7 << 4);   // Set AFRH9 to AF7 (UART1 TX)

    /************** Configure uart module ********************/
    /* Enable clock access to uart1 */
    RCC->APB2ENR |= UART1EN;

    /* Configure baudrate */
    uart_set_baudrate(USART1, APB2_CLK, UART_BAUDRATE);

    /* Configure the transfer direction */
    USART1->CR1 = CR1_TE;

    /* Enable uart module */
    USART1->CR1 |= CR1_UE;
}

char uart1_read(void)
{
	/*Make sure the receive data register is not empty */
    while (!(USART1->SR & SR_RXNE)) {}

    /*Read data */
    return USART1->DR;
}

void uart1_write(int ch)
{
    /* Make sure the transmit data register is empty */
    while (!(USART1->SR & SR_TXE)) {}

    /* Write to transmit data register */
    USART1->DR = (ch & 0xFF);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}