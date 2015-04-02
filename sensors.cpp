#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"
#include "stm32f0xx_i2c.h"

#include "main.h"
#include "settings.h"
#include "gps.h"
#include "dcm.h"
#include "motors.h"
#include "recv.h"
#include "sensors.h"


sens_common sensor;

gyro::gyro() {
	address = (GYRO_ADD & 0x7F) << 1;
	x = y = z = 0;
	// setting up ITG
	// 8KHz sampling, no full scale
	sensor.writeDevice(address, DLPF_FS, 0x00);
	// 400 Hz sampling rate
	sensor.writeDevice(address, SMPLRT_DVI, 19);
}

void gyro::update() {
	x = GYRO_X_SYM sensor.readDevice(address, GYRO_XOUT_H);
	y = GYRO_Y_SYM sensor.readDevice(address, GYRO_YOUT_H);
	z = GYRO_Z_SYM sensor.readDevice(address, GYRO_ZOUT_H);
}


void sens_common::writeDevice(uint8_t address, uint8_t registerAddress, uint8_t data){
	while(I2C_GetFlagStatus(I2C2, I2C_ISR_BUSY) != RESET); // check no trasmission in progress
	I2C_GenerateSTART(I2C2, ENABLE); // generate start
	I2C_SendData(I2C1, address); // send device address
	I2C_SendData(I2C1, (uint8_t)registerAddress); // send register address
	while(I2C_GetFlagStatus(I2C2, I2C_ISR_TC) == RESET); // wait for trasmission complete
	I2C_SendData(I2C2, (uint8_t)data); // sending data
	while(I2C_GetFlagStatus(I2C2, I2C_ISR_TC) == RESET); // wait for trasmission complete
	I2C_GenerateSTOP(I2C2, ENABLE); // set stop bit

}

uint16_t sens_common::readDevice(uint8_t address, uint8_t registerAddress){
    uint16_t data=0;
    uint8_t data_buffer[2] = {0, 0};

    while(I2C_GetFlagStatus(I2C2, I2C_ISR_BUSY) != RESET); // check no trasmission in progress
    I2C_TransferHandling(I2C2, address, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
    while(I2C_GetFlagStatus(I2C2, I2C_ISR_TXIS) == RESET); // wait for TX flag set
    I2C_SendData(I2C2, (uint8_t)registerAddress); // send data
    while(I2C_GetFlagStatus(I2C2, I2C_ISR_TC) == RESET); // waiting trasmission complete
    I2C_TransferHandling(I2C2, address, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read); // config to receive

    uint8_t data_index = 0;

    I2C_AcknowledgeConfig(I2C2, ENABLE); // Need ACK for burst read
    while(data_index != 1) {
    	while(I2C_GetFlagStatus(I2C2, I2C_ISR_RXNE) == RESET);
    	data_buffer[data_index] = I2C_ReceiveData(I2C2);
    	data_index++;
    }
    I2C_AcknowledgeConfig(I2C2, DISABLE);

    I2C_ClearFlag(I2C2, I2C_ICR_STOPCF); // clear stop bit

    // composing data_buffer in data to return
    data = (data_buffer[0] << 8) | data_buffer[1];

    return data;

}


mag::mag() {
	address = (GYRO_ADD & 0x7F) << 1;
	x = y = z = 0;
	// setting up ITG
	// 8KHz sampling, no full scale
	sensor.writeDevice(address, DLPF_FS, 0x00);
	// 400 Hz sampling rate
	sensor.writeDevice(address, SMPLRT_DVI, 19);
}

void mag::update() {
	x = GYRO_X_SYM sensor.readDevice(address, GYRO_XOUT_H);
	y = GYRO_Y_SYM sensor.readDevice(address, GYRO_YOUT_H);
	z = GYRO_Z_SYM sensor.readDevice(address, GYRO_ZOUT_H);
}

acc::acc() {
	address = (GYRO_ADD & 0x7F) << 1;
	x = y = z = 0;
	// setting up ITG
	// 8KHz sampling, no full scale
	sensor.writeDevice(address, DLPF_FS, 0x00);
	// 400 Hz sampling rate
	sensor.writeDevice(address, SMPLRT_DVI, 19);
}

void acc::update() {
	x = GYRO_X_SYM sensor.readDevice(address, GYRO_XOUT_H);
	y = GYRO_Y_SYM sensor.readDevice(address, GYRO_YOUT_H);
	z = GYRO_Z_SYM sensor.readDevice(address, GYRO_ZOUT_H);
}
