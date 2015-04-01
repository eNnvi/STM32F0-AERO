#include "gps.h"
#include "settings.h"
#include <math.h>

// check if not using both ortodromia and lossodromia
#if defined(__GPS_USE_ORTO) && defined(__GPS_USE_LOSSO)
#error "GPS CAN'T USE BOTH LOSSODROMIA AND ORTODROMIA"
#endif

typedef struct gps {
	double fi, lambda;
	double fic, lambdac;
	double TC;

public:
	gps() {
		gps_init();
		fi = get_fi();
		lambda = get_lambda();
	}

	void update() {
		fi = get_fi();
		lambda = get_lambda();
	}

	double get_tc_to(double dest_fi, double dest_lambda) {
	#ifdef __GPS_USE_ORTO
			return atan(1/(tan(tan(dest_fi)*cos(fi)/sin(dest_lambda-lambda) - sin(fi)/tan(dest_lambda-lambda))));
	#endif
	#ifdef __GPS_USE_LOSSO // Not implemented yet
			return ;
	#endif
	}
	double get_dist_to(double dest_fi, double dest_lambda) {
	#ifdef __GPS_USE_ORTO
			return acos(cos(90-fi)*cos(90-dest_fi) + sin(90+fi)*sin(90-dest_fi)*cos(dest_lambda-lambda));
	#endif
	#ifdef __GPS_USE_LOSSO // Not implemented yet
			return;
	#endif
	}

private:
	double get_fi() {

	}

	double get_lambda() {

	}

	void gps_init() {
		// wait for valid fix
	}

};
