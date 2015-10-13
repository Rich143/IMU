//
//  Magnetometer.h
//  
//
//  Created by Richard Matthews on 2015-09-13.
//
//

#ifndef ____Magnetometer__
#define ____Magnetometer__

#include "common.h"
#include "IMU.h"

#define MAG_SLA_ADDR   0b0011110

//---- Magnetometer Registers ----------

#define MAG_CRA_REG_M 0x00 // magnetomer control register a
#define MAG_TEMP_EN 7  // 0: temperature sensor disabled 1: enabled
#define MAG_DO2 4 // see table 72 for the minimum data output rate
#define MAG_DO1 3
#define MAG_DO0 2
#define MAG_RATE_30HZ 0b00010100


#define MAG_CRB_REG_M 0x01 // magnetomer control register b
#define MAG_GN2 7 // see table 75 for gain settings
#define MAG_GN1 6
#define MAG_GN0 5

#define MAG_MR_REG_M  0x02 // mode select register
#define MD1 1 // see table 78 for mode selection
#define MD0 0

#define MAG_OUT_X_H_M 0x03 // high X measurement
#define MAG_OUT_X_L_M 0x04 // low X measurement
#define MAG_OUT_Z_H_M 0x05 // Z
#define MAG_OUT_Z_L_M 0x06
#define MAG_OUT_Y_H_M 0x07 // Y
#define MAG_OUT_Y_L_M 0x08

#define MAG_SR_REG_M 0x09
#define MAG_LOCK 1 // data output register lock, once first measurement register is read, bit is set
#define MAG_DRDY 0 // Data ready, set once new set of measurements ready

#define MAG_TEMP_OUT_H_M 0x31 // high temp out
#define MAG_TEMP_OUT_L_M 0x32 // low temp out, only the high 4 bits can be read, 8LSB/deg


//***** Raw Data Array Indices ****//
// Big endian format
#define MAG_LOW_X 1
#define MAG_HIGH_X 0
#define MAG_LOW_Y 5
#define MAG_HIGH_Y 4
#define MAG_LOW_Z 3
#define MAG_HIGH_Z 2

#define MAG_GN 0b001 // The GN bits in MAG_CRB_REG_M, set to ±1.3gauss
#define MAG_GN_SCALE_XY 1100 // X and Y LSB/gauss
#define MAG_GN_SCALE_Z 980   // Z LSB/gauss

PUBLIC tStatus MAG_Init();
PUBLIC tStatus Mag_ReadMag(Vector *v);

#endif /* defined(____Magnetometer__) */
