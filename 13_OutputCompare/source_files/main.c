#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"


int main(void)
{
	gpio_init();
	tim2_pa5_output_compare();

    while (1)
    {


    }
}