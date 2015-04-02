#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

#include "main.h"
#include "settings.h"
#include "gps.h"
#include "dcm.h"
#include "motors.h"
#include "recv.h"
#include "sensors.h"


extern uint64_t millis_count = 0;

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	SysTick_Config(48000); // 1ms systick

	Recv_init();

	Sensors_init();


	// Setting up Variables
	gyro g;
	acc a;
	mag m;
	uint64_t time = 0;

	// Init complete
	GPIOC->BSRR = GPIO_BSRR_BS_9; // led showing activity

	time = micros();
    while(1)
    {
    	g.update();
    	a.update();
    	m.update();
    	MahonyAHRSupdate(g.x, g.y, g.z, a.x, a.y, a.z, m.x, m.y, m.z);
    }
    return 0;
}

void SysTick_Handler(void) {
	millis_count++;
}


uint64_t micros() {
	return millis_count * 1000 + 1000 - SysTick->VAL;
}

uint64_t millis() {
	return millis_count;
}

void delay(uint64_t del) {
	uint64_t tmp = millis();
	while(millis() - tmp < del);
}

void delay_uS(uint64_t del) {
	uint64_t tmp = micros();
	while(micros() - tmp < del);
}

void I2C_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

    /* Configure the I2C clock source. The clock is derived from the HSI */
  //  RCC_I2CCLKConfig(RCC_I2C1CLK_HSI);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);


    //Configure pins: SCL and SDA ------------------
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
    I2C_InitStructure.I2C_DigitalFilter = 0x00;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00; // MPU6050 7-bit adress = 0x68, 8-bit adress = 0xD0;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    //I2C_InitStructure.I2C_Timing = 0xA0120227;
    I2C_InitStructure.I2C_Timing = 0x20310A0D;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    I2C_Init(I2C2, &I2C_InitStructure);

    I2C_Cmd(I2C2, ENABLE);

}

void RCC_init(void) {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}

void Motors_init(void) {

}

void Recv_init(void) {
	// GPIOC 0 - 6 - INPUT (Recv int)
	GPIO_InitTypeDef gpioCFG;
	gpioCFG.GPIO_Mode = GPIO_Mode_IN;
	gpioCFG.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioCFG.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	gpioCFG.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpioCFG);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource4);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);

	EXTI_InitTypeDef extiCFG;
	extiCFG.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4 | EXTI_Line5 | EXTI_Line6;
	extiCFG.EXTI_Mode = EXTI_Mode_Interrupt;
	extiCFG.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	extiCFG.EXTI_LineCmd = ENABLE;
	EXTI_Init(&extiCFG);

	NVIC_SetPriority(EXTI0_1_IRQn, 1);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	NVIC_SetPriority(EXTI2_3_IRQn, 1);
	NVIC_EnableIRQ(EXTI2_3_IRQn);
	NVIC_SetPriority(EXTI4_15_IRQn, 1);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void Sensors_init(void) {
	I2C_init();
}

void GPS_init(void) {

}

void Uart_init(void) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;

	USART_Init(USART1, &USART_InitStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
}

void Misc_init(void) {
	GPIO_InitTypeDef gpioCFG;
	gpioCFG.GPIO_Mode = GPIO_Mode_OUT;
	gpioCFG.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioCFG.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpioCFG.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpioCFG);
}
