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


const uint8_t SMPLRT_DVI  = 0x15;
const uint8_t DLPF_FS     = 0x16;
const uint8_t TEMP_OUT_H  = 0x1B;
const uint8_t TEMP_OUT_L  = 0x1C;
const uint8_t GYRO_XOUT_H = 0x1D;
const uint8_t GYRO_XOUT_L = 0x1E;
const uint8_t GYRO_YOUT_H = 0x1F;
const uint8_t GYRO_YOUT_L = 0x20;
const uint8_t GYRO_ZOUT_H = 0x21;
const uint8_t GYRO_ZOUT_L = 0x22;

#endif // __SENSORS_H__
