#ifndef __SETTINGS_H__
#define __SETTINGS_H__

// PID SETTINGS
#define ROLL_P
#define ROLL_I
#define ROLL_D

#define PITCH_P
#define PITCH_I
#define PITCH_D

#define YAW_P
#define YAW_I
#define YAW_D

#define THR_P
#define THR_I
#define THR_D

// recv settings


// eng settings



// i2c settings


// gyro settings
#define GYRO_ADD 0xD0
#define GYRO_X_SYM
#define GYRO_Y_SYM
#define GYRO_Z_SYM

// acc settings
#define ACC_ADD 0x30
#define ACC_X_SYM
#define ACC_Y_SYM
#define ACC_Z_SYM

// mag settings
#define MAG_ADD 0x30
#define MAG_X_SYM
#define MAG_Y_SYM
#define MAG_Z_SYM

// gps settings
#define __GPS_USE_ORTO  // use ortodromia, long distances, more accurate
//#define __GPS_USE_LOSSO // use lossodromia, short distances, faster


// Do not tuch under this line
#define FLIGHT_MODE_WAYPOINT 0x01
#define FLIGHT_MODE_HOLD 0x02
#define FLIGHT_MODE_GPS_HOLD 0x03
#define FLIGHT_MODE_NORMAL 0x00

#define MOTOR_ENABLED_EN 0x01
#define MOTOR_ENABLED_NE 0x00

#define RECV_THR 0
#define RECV_AIL 1
#define RECV_ELEV 2
#define RECV_RUDDER 3
#define RECV_AUX1 4
#define RECV_AUX2 5
#define RECV_AUX3 6

#endif // __SETTINGS_H__
