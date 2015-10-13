//
//  Magnetometer.c
//  
//
//  Created by Richard Matthews on 2015-09-13.
//
//

#include <stdio.h>
#include "Debug/Debug.h"
#include "common.h"
#include "Magnetometer.h"
#include "TWI/TWI.h"

// @Brief read Mag
PUBLIC tStatus Mag_ReadMag(Vector *v)
{
    uint8_t mag_raw[6];
    
    if (TWI_RegisterRead_Multiple(MAG_OUT_X_H_M, mag_raw, 6, MAG_SLA_ADDR) != SUCCESS) {
        printf("MAG ERROR: reading accel data.\n");
        return ERROR;
    }
    
//     printf("--Bytes From Mag---\n");
//     printf("xhi: "); print_binary_8(mag_raw[MAG_HIGH_X]);
//     printf(" xlo: "); print_binary_8(mag_raw[MAG_LOW_X]);
//     printf("\nyhi: "); print_binary_8(mag_raw[MAG_HIGH_Y]);
//     printf(" ylo: "); print_binary_8(mag_raw[MAG_LOW_Y]);
//     printf("\nzhi: "); print_binary_8(mag_raw[MAG_HIGH_Z]);
//     printf(" zlo: "); print_binary_8(mag_raw[MAG_LOW_Z]);

    int16_t magX = (int16_t)((mag_raw[MAG_HIGH_X]<<8) | mag_raw[MAG_LOW_X]);
    int16_t magY = (int16_t)((mag_raw[MAG_HIGH_Y]<<8) | mag_raw[MAG_LOW_Y]);
    int16_t magZ = (int16_t)((mag_raw[MAG_HIGH_Z]<<8) | mag_raw[MAG_LOW_Z]);
   
//     printf("\n--MAG Before Scaling--\n");
//     printf("X: "); print_binary_16(magX); printf(" Y: "); print_binary_16(magY);
//     printf(" Z: "); print_binary_16(magZ); printf("\n");
//     printf("X: %d, Y: %d, Z: %d\n", magX, magY, magZ); 

    magX = magX / MAG_GN_SCALE_XY; // scale the raw mag values by the gain to get units of gauss
    magY = magY / MAG_GN_SCALE_XY;
    magZ = magZ / MAG_GN_SCALE_Z;
    
    v->x = magX;
    v->y = magY;
    v->z = magZ;
    
    return SUCCESS;
}

//@Brief: Initialize the magnetometer
//        30Hz
//        ±1.3 gauss range
//        x and y gain 1100 LSB / gauss
//        z gain 980 LSB / gauss
PUBLIC tStatus MAG_Init() {
    tStatus status_return = SUCCESS;
    
    uint8_t regAVal = MAG_RATE_30HZ; // 30 HZ rate
//     uint8_t regBVal = _BV(MAG_GN0); // ±1.3 gauss range, x and y gain: 1100 LSB/gauss, z gain 980 LSB/gauss
    uint8_t regBVal = _BV(MAG_GN0) | _BV(MAG_GN1); // ±2.5 gauss range, x and y gain: 670LSB/gauss, z gain 600 LSB/Gauss
    uint8_t regMRVal = 0; // continuous conversion mode
    
    status_return |= TWI_RegisterWrite(MAG_CRA_REG_M, regAVal , MAG_SLA_ADDR);
    status_return |= TWI_RegisterWrite(MAG_CRB_REG_M, regBVal, MAG_SLA_ADDR);
    status_return |= TWI_RegisterWrite(MAG_MR_REG_M, regMRVal, MAG_SLA_ADDR);
                                       
    if (status_return != SUCCESS) {
       printf("MAG ERROR: failed to initalize magnetometer\n");
       return ERROR;
    } else {
       return SUCCESS;
    }
}
