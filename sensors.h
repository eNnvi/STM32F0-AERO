#ifndef __SENSORS_H__
#define __SENSORS_H__

class gyro {
protected:
	char address;
	int x, y, z;

public:
	gyro();
	void update();

};

class mag {


};

class acc {


};


#endif // __SENSORS_H__
