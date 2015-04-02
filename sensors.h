#ifndef __SENSORS_H__
#define __SENSORS_H__

class gyro {
protected:
	char address;

public:
	int x, y, z;
	gyro();
	void update();

};

class mag {
protected:
	char address;

public:
	int x, y, z;
	mag();
	void update();



};

class acc {
protected:
	char address;

public:
	int x, y, z;
	acc();
	void update();

};


class sens_common {
public:
	void writeDevice(uint8_t address, uint8_t registerAddress, uint8_t data);
	uint16_t readDevice(uint8_t address, uint8_t registerAddress);
};


const uint8_t GYRO_SMPLRT_DVI  = 0x15;
const uint8_t GYRO_DLPF_FS     = 0x16;
const uint8_t GYRO_TEMP_OUT_H  = 0x1B;
const uint8_t GYRO_TEMP_OUT_L  = 0x1C;
const uint8_t GYRO_XOUT_H = 0x1D;
const uint8_t GYRO_XOUT_L = 0x1E;
const uint8_t GYRO_YOUT_H = 0x1F;
const uint8_t GYRO_YOUT_L = 0x20;
const uint8_t GYRO_ZOUT_H = 0x21;
const uint8_t GYRO_ZOUT_L = 0x22;

const uint8_t ACC_XOUT_H = 0x32;
const uint8_t ACC_XOUT_L = 0x33;
const uint8_t ACC_YOUT_H = 0x34;
const uint8_t ACC_YOUT_L = 0x35;
const uint8_t ACC_ZOUT_H = 0x36;
const uint8_t ACC_ZOUT_L = 0x37;
const uint8_t ACC_RATE_400 = 0x0C;
const uint8_t ACC_BW_RATE = 0x2C;
const uint8_t ACC_POWER_CTL = 0x2D;
const uint8_t ACC_INT_ENABLE = 0x2E;
const uint8_t ACC_DATA_FORMAT = 0x31;
const uint8_t ACC_DATA_OUT = 0x32;
const uint8_t ACC_FIFO_CTL = 0x38;
const uint8_t ACC_POWER_MEAS = 0x08;
const uint8_t ACC_FULL_RANGE = 0x08;
const uint8_t ACC_RANGE_2G = 0x00;
const uint8_t ACC_RANGE_4G = 0x01;
const uint8_t ACC_RANGE_8G = 0x02;
const uint8_t ACC_RANGE_16G = 0x03;
const uint8_t ACC_FIFO_STREAM = 0x80;


const uint8_t MAG_XOUT_H = 0x32;
const uint8_t MAG_XOUT_L = 0x33;
const uint8_t MAG_YOUT_H = 0x34;
const uint8_t MAG_YOUT_L = 0x35;
const uint8_t MAG_ZOUT_H = 0x36;
const uint8_t MAG_ZOUT_L = 0x37;




#endif // __SENSORS_H__
