#ifndef __MAIN_H__
#define __MAIN_H__

extern "C" {
	uint64_t micros();
	uint64_t millis();
	void delay(uint64_t del);
	void delay_uS(uint64_t del);
	void I2C_init(void);
	void RCC_init(void);
	void Motors_init(void);
	void Recv_init(void);
	void Sensors_init(void);
	void GPS_init(void);
	void Uart_init(void);
	void Misc_init(void);
}

#endif // __MAIN_H__
