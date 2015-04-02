#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

#include "main.h"
#include "settings.h"
#include "gps.h"
#include "dcm.h"
#include "motors.h"
#include "recv.h"
#include "sensors.h"
#include <math.h>

// check if not using both ortodromia and lossodromia
#if defined(__GPS_USE_ORTO) && defined(__GPS_USE_LOSSO)
#error "GPS CAN'T USE BOTH LOSSODROMIA AND ORTODROMIA"
#endif


gps::gps() {
	gps_init();
	fi = get_fi();
	lambda = get_lambda();
}

void gps::update() {
	fi = get_fi();
	lambda = get_lambda();
}

double gps::get_tc_to(double dest_fi, double dest_lambda) {
#ifdef __GPS_USE_ORTO
		return atan(1/(tan(tan(dest_fi)*cos(fi)/sin(dest_lambda-lambda) - sin(fi)/tan(dest_lambda-lambda))));
#endif
#ifdef __GPS_USE_LOSSO // Not implemented yet
		return ;
#endif
}

double gps::get_dist_to(double dest_fi, double dest_lambda) {
#ifdef __GPS_USE_ORTO
		return acos(cos(90-fi)*cos(90-dest_fi) + sin(90+fi)*sin(90-dest_fi)*cos(dest_lambda-lambda));
#endif
#ifdef __GPS_USE_LOSSO // Not implemented yet
		return;
#endif
}

double gps::get_fi() {
	double tmp_fi = 0;
	return tmp_fi;
}

double gps::get_lambda() {
	double tmp_lambda = 0;
	return tmp_lambda;
}

void gps::gps_init() {
	// wait for valid fix
}
