#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

#include "main.h"
#include "settings.h"
#include "gps.h"
#include "dcm.h"
#include "motors.h"
#include "recv.h"
#include "sensors.h"

// Using timer 6 to compare pwm
// The first risign pin will enable the timer, the other will only store the actual count
// Only the last falling pin will stop the timer

// 0 - THR
// 1 - AIL
// 2 - ELEV
// 3 - RUDDER
// 4 - AUX1
// 5 - AUX2
// 6 - AUX3

uint8_t enabled_pins = 0b10000000;
uint32_t pins_value[7];
uint32_t recv_value[7];

extern uint64_t millis_count;

extern "C" {
	void EXTI0_1IRQHandler(void) {
		if((EXTI->IMR & EXTI_IMR_MR0) && (EXTI->PR & EXTI_PR_PR0)) { // line 0 interrupt
			if((GPIOC->IDR & (1 << 0)) == (1 << 0)) { //rising
				if((TIM6->CR1 & TIM_CR1_CEN) == (TIM_CR1_CEN)) { // timer is enabled
						pins_value[0] = TIM_GetCounter(TIM6); // reading actual state of timer
						enabled_pins |= 1; // pin 0 is enabled
						EXTI_ClearITPendingBit(EXTI_Line0);
						return;
				}
				// timer is not enabled
				enabled_pins |= 1; // pin 0 enabled
				TIM_Cmd(TIM6, ENABLE); // timer enabled
				TIM_SetCounter(TIM6, 0); // resetting timer
				pins_value[0] = 0;
				EXTI_ClearITPendingBit(EXTI_Line0);
				return;
			}
			// falling
			recv_value[0] = pins_value[0] - TIM_GetCounter(TIM6);
			enabled_pins &= ~(1); // clear pin 0 bit
			if(enabled_pins == 0x00)  TIM_Cmd(TIM6, DISABLE);  // stop the timer
			return;
		}

		if((EXTI->IMR & EXTI_IMR_MR1) && (EXTI->PR & EXTI_PR_PR1)) { // line 1 interrupt
			if((GPIOC->IDR & (1 << 1)) == (1 << 1)) { //rising
				if((TIM6->CR1 & TIM_CR1_CEN) == (TIM_CR1_CEN)) { // timer is enabled
						pins_value[1] = TIM_GetCounter(TIM6); // reading actual state of timer
						enabled_pins |= (1 << 1); // pin 1 is enabled
						EXTI_ClearITPendingBit(EXTI_Line1);
						return;
				}
				// timer is not enabled
				enabled_pins |= (1 << 1); // pin 1 enabled
				TIM_Cmd(TIM6, ENABLE); // timer enabled
				TIM_SetCounter(TIM6, 0); // resetting timer
				pins_value[1] = 0;
				EXTI_ClearITPendingBit(EXTI_Line1);
				return;
			}
			// falling
			recv_value[1] = pins_value[1] - TIM_GetCounter(TIM6);
			enabled_pins &= ~(1 << 1); // clear pin 1 bit
			if(enabled_pins == 0x00) TIM_Cmd(TIM6, DISABLE);  // stop the timer
			return;
		}

	}

	void EXTI2_3IRQHandler(void) {

	}

	void EXTI4_15IRQHandler(void) {

	}
}
