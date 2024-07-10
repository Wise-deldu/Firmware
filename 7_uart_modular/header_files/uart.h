#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"


void uart1_tx_init(void);
void uart1_write(int ch);


#endif /* UART_H_ */
