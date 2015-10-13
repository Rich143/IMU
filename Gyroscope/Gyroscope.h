//
//  Gyroscope.h
//  
//
//  Created by Richard Matthews on 2015-09-13.
//
//

#ifndef ____Gyroscope__
#define ____Gyroscope__

#include "common.h"
#include "IMU.h"

#define GYRO_SLA_ADDR 0b1101011
#define L3GD20_ID                0xD4
#define L3GD20H_ID               0xD7

// Sensitivity Values
/* ----- Exact Values --------
#define GYRO_SENSITIVITY_250DPS 8.75 // mdps / digit
#define GYRO_SENSITIVITY_250DPS 17.50 // mdps / digit
#define GYRO_SENSITIVITY_250DPS 70 // mdps / digit
*/
// Rounded so can use fixed point math
#define GYRO_SENSITIVITY_250DPS 9 // mdps / digit
#define GYRO_SENSITIVITY_500DPS 18 // mdps / digit
#define GYRO_SENSITIVITY_2000DPS 70 // mdps / digit

typedef enum {
    GYRO_RANGE_250DPS = 250,
    GYRO_RANGE_500DPS = 500,
    GYRO_RANGE_2000DPS = 2000
}tGyroRange;

// ------------ Registers ---------------------

// set the MSB of the address to high to enable register address to be incremented after each read/write
#define GYRO_AUTO_INCREMENT 0x80

                                            // DEFAULT    TYPE
#define GYRO_WHO_AM_I            0x0F   // 11010100   r
#define GYRO_CTRL_REG1           0x20   // 00000111   rw
#define GYRO_CTRL_REG2           0x21   // 00000000   rw
#define GYRO_CTRL_REG3           0x22   // 00000000   rw
#define GYRO_CTRL_REG4           0x23   // 00000000   rw
#define GYRO_CTRL_REG5           0x24   // 00000000   rw
#define GYRO_REFERENCE           0x25   // 00000000   rw
#define GYRO_OUT_TEMP            0x26   //            r
#define GYRO_STATUS_REG          0x27   //            r
#define GYRO_OUT_X_L             0x28   //            r
#define GYRO_OUT_X_H             0x29   //            r
#define GYRO_OUT_Y_L             0x2A   //            r
#define GYRO_OUT_Y_H             0x2B   //            r
#define GYRO_OUT_Z_L             0x2C   //            r
#define GYRO_OUT_Z_H             0x2D   //            r
#define GYRO_FIFO_CTRL_REG       0x2E   // 00000000   rw
#define GYRO_FIFO_SRC_REG        0x2F   //            r
#define GYRO_INT1_CFG            0x30   // 00000000   rw
#define GYRO_INT1_SRC            0x31   //            r
#define GYRO_TSH_XH              0x32   // 00000000   rw
#define GYRO_TSH_XL              0x33   // 00000000   rw
#define GYRO_TSH_YH              0x34   // 00000000   rw
#define GYRO_TSH_YL              0x35   // 00000000   rw
#define GYRO_TSH_ZH              0x36   // 00000000   rw
#define GYRO_TSH_ZL              0x37   // 00000000   rw
#define GYRO_INT1_DURATION       0x38    // 00000000   rw

//***** Raw Data Array Indices ****//
// Little endian format
#define LOW_X 0
#define HIGH_X 1
#define LOW_Y 2
#define HIGH_Y 3
#define LOW_Z 4
#define HIGH_Z 5

PRIVATE tGyroRange _range; // The current range setting


PUBLIC tStatus GYRO_Init(tGyroRange range);
PUBLIC tStatus GYRO_ReadGyro(Attitude* v);

#endif /* defined(____Gyroscope__) */
