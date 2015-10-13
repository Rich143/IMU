#ifndef __IMU_H__
#define __IMU_H__

#include <avr/io.h>
#include "common.h"

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} Vector;

typedef struct {
    double x;
    double y;
    double z;
} Vector_double;

typedef struct {
    // roll, pitch and yaw angles in degrees
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} Attitude;

#define sq(x) ((x)*(x))


PUBLIC tStatus IMU_Init();
PUBLIC tStatus IMU_Read(Attitude *attitude, long lastRead);

#include "Uart/uart.h"
#include "TWI/TWI.h"
#include "Accelerometer/Accelerometer.h"
#include "Magnetometer/Magnetometer.h"
#include "Gyroscope/Gyroscope.h"

#endif
