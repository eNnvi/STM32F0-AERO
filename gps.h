#ifndef __GPS_H__
#define __GPS_H__
#include <math.h>

class gps {
	double fi, lambda;
	double fic, lambdac;
	double TC;

public:
	gps(void);
	void update();
	double get_tc_to(double dest_fi, double dest_lambda);
	double get_dist_to(double dest_fi, double dest_lambda);

private:
	double get_fi();
	double get_lambda();
	void gps_init();

};

#endif // __GPS_H__
