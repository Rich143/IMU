//
//  Accelerometer.h
//  
//
//  Created by Richard Matthews on 2015-09-13.
//
//

#ifndef ____Accelerometer__
#define ____Accelerometer__

#include "common.h"
#include "IMU.h"

#define ACCEL_SLA_ADDR 0b0011001


// ------------ Registers ---------------------

// set the MSB of the address to high to enable register address to be incremented after each read/write
#define ACCEL_AUTO_INCREMENT 0x80

//                                          DEFAULT    TYPE
#define ACCEL_CTRL_REG1_A         0x20   // 00000111   rw
#define X_EN 0
#define Y_EN 1
#define Z_EN 2

#define ACCEL_RATE_50HZ 0b01000000
#define ACCEL_RATE_25HZ 0b00110000
#define ACCEL_RATE_10HZ 0b00100000
#define ACCEL_RATE_1HZ  0b00010000

#define ACCEL_CTRL_REG2_A         0x21   // 00000000   rw
#define ACCEL_CTRL_REG3_A         0x22   // 00000000   rw
#define ACCEL_CTRL_REG4_A         0x23   // 00000000   rw
#define ACCEL_BE 6
#define ACCEL_HR 3

#define ACCEL_CTRL_REG5_A         0x24   // 00000000   rw
#define ACCEL_CTRL_REG6_A         0x25   // 00000000   rw
#define ACCEL_REFERENCE_A         0x26   // 00000000   r
#define ACCEL_STATUS_REG_A        0x27   // 00000000   r
#define ACCEL_OUT_X_H_A           0x28
#define ACCEL_OUT_X_L_A           0x29
#define ACCEL_OUT_Y_H_A           0x2A
#define ACCEL_OUT_Y_L_A           0x2B
#define ACCEL_OUT_Z_H_A           0x2C
#define ACCEL_OUT_Z_L_A           0x2D
#define ACCEL_FIFO_CTRL_REG_A     0x2E
#define ACCEL_FIFO_SRC_REG_A      0x2F
#define ACCEL_INT1_CFG_A          0x30
#define ACCEL_INT1_SOURCE_A       0x31
#define ACCEL_INT1_THS_A          0x32
#define ACCEL_INT1_DURATION_A     0x33
#define ACCEL_INT2_CFG_A          0x34
#define ACCEL_INT2_SOURCE_A       0x35
#define ACCEL_INT2_THS_A          0x36
#define ACCEL_INT2_DURATION_A     0x37
#define ACCEL_CLICK_CFG_A         0x38
#define ACCEL_CLICK_SRC_A         0x39
#define ACCEL_CLICK_THS_A         0x3A
#define ACCEL_TIME_LIMIT_A        0x3B
#define ACCEL_TIME_LATENCY_A      0x3C
#define ACCEL_TIME_WINDOW_A       0x3D



//***** Raw Data Array Indices ****//
// Little endian format
#define ACCEL_LOW_X 0
#define ACCEL_HIGH_X 1
#define ACCEL_LOW_Y 2
#define ACCEL_HIGH_Y 3
#define ACCEL_LOW_Z 4
#define ACCEL_HIGH_Z 5

//***** Sensitivity and Range Values ******//
// Using cgs units
// gauss for mag values, and cm/second^2 for accel values
// raw values are scaled appropriately

PRIVATE const uint8_t ACC_LA_SO = 1; // accel sensitivity in mg/LSB
PRIVATE const uint8_t ACC_LA_FS = 0b00; // FS bits in control register 4 to determine range and sensitivity

//***** Functions **********/
PUBLIC tStatus Accel_Attitude(Attitude* attitude, boolean* readingValid);
PUBLIC tStatus Accel_ReadAccel(Vector *v);
PUBLIC tStatus Accel_Init(void);

#endif /* defined(____Accelerometer__) */
