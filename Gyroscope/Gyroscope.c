//
//  Gyroscope.cpp
//  
//
//  Created by Richard Matthews on 2015-09-13.
//
//

#include "Gyroscope.h"
#include "common.h"
#include "TWI/TWI.h"

// @Brief Read the gyroscope and output data converted to mdps
// @v Output: Attitude representing x,y and z roll rates in milli dps
PUBLIC tStatus GYRO_ReadGyro(Attitude* v) {
    uint8_t raw_data[6] = {0};
    
    if (TWI_RegisterRead_Multiple((GYRO_OUT_X_L | GYRO_AUTO_INCREMENT), raw_data, 6, GYRO_SLA_ADDR) != SUCCESS) {
        // Serial.println("GRYO ERROR: reading gryo data.");
        return ERROR;
    }
    
    int16_t gyroX = (raw_data[HIGH_X]<<8) | raw_data[LOW_X];
    int16_t gyroY = (raw_data[HIGH_Y]<<8) | raw_data[LOW_Y];
    int16_t gyroZ = (raw_data[HIGH_Z]<<8) | raw_data[LOW_Z];
    
    switch (_range) {
        case GYRO_RANGE_250DPS:
            gyroX *= GYRO_SENSITIVITY_250DPS;
            gyroY *= GYRO_SENSITIVITY_250DPS;
            gyroZ *= GYRO_SENSITIVITY_250DPS;
            break;
        case GYRO_RANGE_500DPS:
            gyroX *= GYRO_SENSITIVITY_500DPS;
            gyroY *= GYRO_SENSITIVITY_500DPS;
            gyroZ *= GYRO_SENSITIVITY_500DPS;
            break;
        case GYRO_RANGE_2000DPS:
            gyroX *= GYRO_SENSITIVITY_2000DPS;
            gyroY *= GYRO_SENSITIVITY_2000DPS;
            gyroZ *= GYRO_SENSITIVITY_2000DPS;
            break;
        default:
            // Serial.println("GYRO ERROR: Unknown range while attempting to read");
            return ERROR;
            break;
    }


    // *********** CHECK THIS *************
    v->roll = gyroX;
    v->pitch = gyroY;
    v->yaw = gyroZ;
    
    return SUCCESS;
}


// @Brief: Initialize the Gyro
// Checks the gyro is working by reading who am i register and comparing to chip id
// Set 95 Hz output rate
// @Range set the gyro output range to this value
PUBLIC tStatus GYRO_Init(tGyroRange range) {
    tStatus status_return = SUCCESS;
    
    _range = range;
    
    /* Make sure we have the correct chip ID since this checks
     for correct address and that the IC is properly connected */
    uint8_t id;
    if (TWI_RegisterRead(GYRO_WHO_AM_I, &id, GYRO_SLA_ADDR) != SUCCESS) {
        // Serial.println("GYRO ERROR: reading WHO_AM_I register");
        return ERROR;
    }
    
    //Serial.println(id, HEX);
    if ((id != L3GD20_ID) && (id != L3GD20H_ID))
    {
        // Serial.println("GRYO ERROR: WHO_AM_I register contains unexpected value");
        return ERROR;
    }
    
    /* Set CTRL_REG1 (0x20)
     ====================================================================
     BIT  Symbol    Description                                   Default
     ---  ------    --------------------------------------------- -------
     7-6  DR1/0     Output data rate                                   00
     5-4  BW1/0     Bandwidth selection                                00
     3  PD        0 = Power-down mode, 1 = normal/sleep mode          0
     2  ZEN       Z-axis enable (0 = disabled, 1 = enabled)           1
     1  YEN       Y-axis enable (0 = disabled, 1 = enabled)           1
     0  XEN       X-axis enable (0 = disabled, 1 = enabled)           1 */
    
    /* Reset then switch to normal mode and enable all three channels */
    // 95 Hz output rate
    status_return |= TWI_RegisterWrite(GYRO_CTRL_REG1, 0x00, GYRO_SLA_ADDR);
    status_return |= TWI_RegisterWrite(GYRO_CTRL_REG1, 0x0F, GYRO_SLA_ADDR);
    /* ------------------------------------------------------------------ */
    
    /* Set CTRL_REG2 (0x21)
     ====================================================================
     BIT  Symbol    Description                                   Default
     ---  ------    --------------------------------------------- -------
     5-4  HPM1/0    High-pass filter mode selection                    00
     3-0  HPCF3..0  High-pass filter cutoff frequency selection      0000 */
    
    /* Nothing to do ... keep default values */
    /* ------------------------------------------------------------------ */
    
    /* Set CTRL_REG3 (0x22)
     ====================================================================
     BIT  Symbol    Description                                   Default
     ---  ------    --------------------------------------------- -------
     7  I1_Int1   Interrupt enable on INT1 (0=disable,1=enable)       0
     6  I1_Boot   Boot status on INT1 (0=disable,1=enable)            0
     5  H-Lactive Interrupt active config on INT1 (0=high,1=low)      0
     4  PP_OD     Push-Pull/Open-Drain (0=PP, 1=OD)                   0
     3  I2_DRDY   Data ready on DRDY/INT2 (0=disable,1=enable)        0
     2  I2_WTM    FIFO wtrmrk int on DRDY/INT2 (0=dsbl,1=enbl)        0
     1  I2_ORun   FIFO overrun int on DRDY/INT2 (0=dsbl,1=enbl)       0
     0  I2_Empty  FIFI empty int on DRDY/INT2 (0=dsbl,1=enbl)         0 */
    
    /* Nothing to do ... keep default values */
    /* ------------------------------------------------------------------ */
    
    /* Set CTRL_REG4 (0x23)
     ====================================================================
     BIT  Symbol    Description                                   Default
     ---  ------    --------------------------------------------- -------
     7  BDU       Block Data Update (0=continuous, 1=LSB/MSB)         0
     6  BLE       Big/Little-Endian (0=Data LSB, 1=Data MSB)          0
     5-4  FS1/0     Full scale selection                               00
     00 = 250 dps
     01 = 500 dps
     10 = 2000 dps
     11 = 2000 dps
     0  SIM       SPI Mode (0=4-wire, 1=3-wire)                       0 */
    
    /* Adjust resolution if requested */
    switch(range)
    {
        case GYRO_RANGE_250DPS:
            status_return |= TWI_RegisterWrite(GYRO_CTRL_REG4, 0x00, GYRO_SLA_ADDR);
            break;
        case GYRO_RANGE_500DPS:
            status_return |= TWI_RegisterWrite(GYRO_CTRL_REG4, 0x10, GYRO_SLA_ADDR);
            break;
        case GYRO_RANGE_2000DPS:
            status_return |= TWI_RegisterWrite(GYRO_CTRL_REG4, 0x20, GYRO_SLA_ADDR);
            break;
    }
    /* ------------------------------------------------------------------ */
    
    /* Set CTRL_REG5 (0x24)
     ====================================================================
     BIT  Symbol    Description                                   Default
     ---  ------    --------------------------------------------- -------
     7  BOOT      Reboot memory content (0=normal, 1=reboot)          0
     6  FIFO_EN   FIFO enable (0=FIFO disable, 1=enable)              0
     4  HPen      High-pass filter enable (0=disable,1=enable)        0
     3-2  INT1_SEL  INT1 Selection config                              00
     1-0  OUT_SEL   Out selection config                               00 */
    
    /* Nothing to do ... keep default values */
    /* ------------------------------------------------------------------ */
    
    if (status_return != SUCCESS) {
        return ERROR;
    } else {
        return SUCCESS;
    }
}
