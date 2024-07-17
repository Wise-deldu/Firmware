#ifndef TIM_H_
#define TIM_H_

#define SR_UIF		(1U<<0)

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void gpio_init(void);
void TIM2_IRQHandler(void);


#endif /* TIM_H_ */