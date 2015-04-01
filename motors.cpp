#include "motors.h"
#include "stm32f0xx.h"

void motors_init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
	TIM15->CR1 |= 0;
}
