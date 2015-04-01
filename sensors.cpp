#include "sensors.h"
#include "stm32f0xx.h"
#include "settings.h"
#include "stm32f0xx_i2c.h"


gyro::gyro() {
	address = GYRO_ADD;
	x = y = z = 0;
}

void gyro::update() {
	uint16_t tmp = 0x00;
	/*I2C_GenerateSTART(I2C2, ENABLE);
	while((I2C2->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY); // check no trasmission in progress
	I2C2->CR2 |= (8 << 16); // number of bits to send
	I2C2->CR2 &= ~I2C_CR2_ADD10; // 7 bit address mode
	I2C2->CR2 |= address; // slave address
	while((I2C2->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY); // check no trasmission in progress
	I2C2->TXDR = address; // sending address
	while((I2C2->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY); // checking ended trasmission
	I2C2->TXDR = 0;
	*/
}


