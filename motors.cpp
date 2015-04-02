#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

#include "main.h"
#include "settings.h"
#include "gps.h"
#include "dcm.h"
#include "motors.h"
#include "recv.h"
#include "sensors.h"

void motors_init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
	TIM15->CR1 |= 0;
}
