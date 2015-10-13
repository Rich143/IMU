//
//  Accelerometer.cpp
//  
//
//  Created by Richard Matthews on 2015-09-13.
//
//

#include "Accelerometer/Accelerometer.h"
#include "common.h"
#include "TWI/TWI.h"
#include <math.h>
#include <stdio.h>

// @return: an attitude vector containing roll and pitch angles in degrees
// @readingValid: false if gravity vector measured >= 2g or <= 0.5g, still returns success in that case
PUBLIC tStatus Accel_Attitude(Attitude* attitude, boolean* readingValid) {
    Vector raw; // the raw acceleration data from the accelerometer, in milli g's
    
    if (SUCCESS != Accel_ReadAccel(&raw)) {
    	(*readingValid) = false;
        return ERROR;
    }

    int forceMagnitudeApprox = abs(raw.x) + abs(raw.y) + abs(raw.z);
    if (forceMagnitudeApprox >= 2000 || forceMagnitudeApprox <= 500) {
    	(*readingValid) = false;
        printf("ACCEL ERROR: Magnitude >= 3000 or <= 500\n");
    	return SUCCESS;
    }
    
//     printf("Before zeroing-> X: %d, Y: %d, Z: %d\n", raw.x, raw.y, raw.z);
//     
//     // set low values to zero to avoid errors in measurement becoming significant
//     if ( abs(raw.x) < 80) {
//         raw.x = 0;
//     } 
//     if (abs(raw.y) < 80) {
//         raw.y = 0;
//     }
//     if (abs(raw.z) < 80) {
//         raw.z = 0;
//     }
// 
// 
//     printf("After zeroing-> X: %d, Y: %d, Z: %d\n", raw.x, raw.y, raw.z);

    double roll  = (atan2(-(double)raw.y, (double)raw.z)*180.0)/M_PI;

    double tmpSqrt = sqrt( sq( ((double)(raw.y)) ) + sq( ((double)(raw.z)) ) ); 
    double pitch = (atan2(((double)raw.x), tmpSqrt)*180.0)/M_PI;
    
    attitude->roll = (int16_t)round(roll);
    attitude->pitch = (int16_t)round(pitch);

    (*readingValid) = true;
    return SUCCESS;
}

// @Brief Read the accelerometer values over the I2C connection, and convert to signed milli g's representation to return
// @v A vector containing the x, y, and z acceleration in signed (two's complement) form in miili g's (g = 9.8ms^2)
// @return Status of the read, ERROR if I2C error, SUCCESS otherwise
tStatus Accel_ReadAccel(Vector *v)
{
    uint8_t raw_data[6] = {0};

    // note that since Accelerometer set up as little endian output, ACCEL_OUT_X_H_A is the low data byte
    if (TWI_RegisterRead_Multiple((ACCEL_OUT_X_H_A|ACCEL_AUTO_INCREMENT), raw_data, 6, ACCEL_SLA_ADDR) != SUCCESS) {
        printf("ACCEL ERROR: reading accel data.\n");
        return ERROR;
    }

    // Assemble in 16 bit format
    // data from the accelerometer is in little endian, two's complement form
    int16_t x = (raw_data[ACCEL_LOW_X] | (raw_data[ACCEL_HIGH_X] << 8));
    int16_t y = (raw_data[ACCEL_LOW_Y] | (raw_data[ACCEL_HIGH_Y] << 8));
    int16_t z = (raw_data[ACCEL_LOW_Z] | (raw_data[ACCEL_HIGH_Z] << 8));

    // Divide by sixteen to arithmetic right shift the value by 4
    // Required since lower four bits are not used by accelerometer and are always zero
    x /= 16;
    y /= 16;
    z /= 16;

    v->x = x;
    v->y = y;
    v->z = z;

    return SUCCESS;
}

// @Brief Initialize the accelerometer
//        ± 2g scale
//        units = milli-g's
//        12 bit resolution
//        little endian data
//        25 Hz refresh rate
//        x, y, z axis enabled
tStatus Accel_Init(void)
{
    tStatus status_return = SUCCESS;

    // Initialize the Accelerometer

    // 1 Hz, XYZ axis enabled
    uint8_t controlReg1Val = ACCEL_RATE_10HZ | _BV(Z_EN) | _BV(Y_EN) | _BV(X_EN);

    // Set FS 00 meaning ±2g scale
    // enable high resolution to give full 12 bits of data
    // set little endian (MSB at low address)
    uint8_t controlReg4Val = ACC_LA_FS<<4 | _BV(ACCEL_HR);

    status_return |= TWI_RegisterWrite(ACCEL_CTRL_REG1_A, controlReg1Val, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_CTRL_REG2_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_CTRL_REG3_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_CTRL_REG4_A, controlReg4Val, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_CTRL_REG5_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_CTRL_REG6_A, 0, ACCEL_SLA_ADDR);

    status_return |= TWI_RegisterWrite(ACCEL_FIFO_CTRL_REG_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_INT1_CFG_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_INT1_THS_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_INT1_DURATION_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_INT2_CFG_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_INT2_THS_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_INT2_DURATION_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_CLICK_CFG_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_CLICK_SRC_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_CLICK_THS_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_TIME_LIMIT_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_TIME_LATENCY_A, 0, ACCEL_SLA_ADDR);
    status_return |= TWI_RegisterWrite(ACCEL_TIME_WINDOW_A, 0, ACCEL_SLA_ADDR);

    // since SUCCESS == 0, and ERROR = -1 (11111111 in two's complement)
    // |= will make status non-zero if there is a return status other than success from a TWI write
    if (status_return != SUCCESS) {
        // Serial.println("ACCEL ERROR: failed to initalize accelerometer");
        return ERROR;
    } else {
        return SUCCESS;
    }
}
