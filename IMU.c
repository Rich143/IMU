#include <stdio.h>
#include "IMU.h"
#include "Uart/uart.h"
#include "TWI/TWI.h"
#include "Accelerometer/Accelerometer.h"
#include "Magnetometer/Magnetometer.h"
#include "Gyroscope/Gyroscope.h"
#include "Timer/Timer.h"

PUBLIC tStatus IMU_Init() {
    if (UART_Init_9600() != SUCCESS) {
        return ERROR;
    }

    if (TWI_Init(NO_INTERNAL_PULLUP) != SUCCESS) {
        printf("Error initializing TWI");
        return ERROR;
    }

    if (MAG_Init() != SUCCESS) {
        printf("Error initializing MAG");
        return ERROR;
    }
   
    if (Accel_Init() != SUCCESS) {
        printf("Error initializing Accelerometer");
        return ERROR;
    }

    if (GYRO_Init(GYRO_RANGE_250DPS) != SUCCESS) {
        printf("Error initializing GYRO");
        return ERROR;
    }

    return SUCCESS;
}

// @attitude: the previous attitude of the sensor, to be updated with the new sensor info
// @lastRead: the time (in milliseconds) that IMU_Read was last called
PUBLIC tStatus IMU_Read(Attitude* attitude, long lastRead) {
    Vector accelRaw = {0};
    Attitude accel = {0};
    Attitude gyro = {0};
    Vector magRaw = {0};

    boolean accel_readingValid = true;
    boolean gyro_readingValid = true;
    boolean mag_readingValid = true;

    if (SUCCESS != Accel_Attitude(&accel, &accel_readingValid)) {
        printf("IMU Error: Reading Accel");
        accel_readingValid = false;
        return ERROR;
    }

    if (SUCCESS != GYRO_ReadGyro(&gyro)) {
        printf("IMU Error: Reading Gyro");
        gyro_readingValid = false;
        return ERROR; 
    }

    if (SUCCESS != Mag_ReadMag(&magRaw)) {
        printf("IMU Error: Reading Mag");
        mag_readingValid = false; 
        return ERROR;
    }
    
    printf("\n---Accel----\n");
    printf("X: %d, Y: %d, Z: %d\n", accelRaw.x, accelRaw.y, accelRaw.z);
//     
//     printf("---Gyro----\n");
//     printf("Roll: %d, Pitch: %d, Yaw: %d\n", gyro.roll, gyro.pitch, gyro.yaw);
// 
//     printf("---Mag----\n");
//     printf("X: %d, Y: %d, Z: %d\n", magRaw.x, magRaw.y, magRaw.z);

    // all readings invalid, return ERROR
    if (!accel_readingValid && !gyro_readingValid && !mag_readingValid) {
        printf("IMU ERROR: All readings invalid");
        return ERROR;
    }
    
//     printf("\n--Gyro--\n");
//     printf("Roll: %d, Pitch: %d, Yaw: %d\n", gyro.roll, gyro.pitch, gyro.yaw);
//     printf("---Attitude---\n");

    if (gyro_readingValid) {
        unsigned long dt = millis() - lastRead;
//         printf("dt = %lu \n", dt);

        // integrate gyro rotation to get change in angle
        // divide by 1000 to convert milli degrees to degrees
        // divide by 1000 to convert milli seconds to seconds
        long pitchChange = ((long)(gyro.pitch)) * dt;
        long rollChange = ((long)(gyro.roll)) * dt;
        long yawChange = ((long)(gyro.yaw)) * dt;
       
        pitchChange /= 1000000;
        rollChange /= 1000000;
        yawChange /= 1000000;

//         printf("dRoll: %d, dPich: %d, dYaw: %d\n", rollChange, pitchChange, yawChange);

        attitude->pitch += pitchChange;
        attitude->roll += rollChange;
        attitude->yaw += yawChange;
    }
   
    if (accel_readingValid) {
        float pitch = ((float)(attitude->pitch));
        float roll = ((float)(attitude->roll));
  
//         printf("float pitch (int16_t) = %d\n", ((int16_t)(pitch)));
//         printf("ACCEL: roll: %d, pitch: %d\n", accel.roll, accel.pitch);

        // apply complementary filter
        pitch = pitch * 0.98 + ((float)(accel.pitch)) * 0.02;
        roll = roll * 0.98 + ((float)(accel.roll)) * 0.02;

        attitude->pitch = ((int16_t)(pitch));
        attitude->roll = ((int16_t)(roll));
    }
    else {
        printf("Accel Reading Invalid");
    }

    return SUCCESS;
}
