/* Name: main.c
 * Author: Richard Matthewss
 * Copyright: This is my code, don't use it! 
 * (You probably don't want to use it anyway...)
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "IMU.h"
#include "Timer/Timer.h"
#include "Scheduler/Scheduler.h"

FILE uart_output = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    stdout = &uart_output;
    
//     printf("starting up\n");
    _delay_ms(1000);

    if (IMU_Init() != SUCCESS) {
        return -1;
    }
    
    Timer_Init();

    printf("initialized\n");

    Attitude attitude = {0};
    Attitude accelAttitude = {0};
    Vector magRaw = {0};
    Attitude gyroRaw = {0};

    unsigned long lastRead = millis();

    INIT_LOOP_1_FREQUENCY(50)
    INIT_LOOP_2_FREQUENCY(1000)

    for(;;){
//         printf("\n------READ-------\n");
//         IMU_Read(&attitude);        
//         Mag_ReadMag(&magRaw);
//         printf("\n-----Mag------\n");
//         printf("X: %d, Y: %d, Z: %d\n", magRaw.x, magRaw.y, magRaw.z);
//         GYRO_ReadGyro(&gyroRaw);
//         printf("\n-----GYRO------\n");
//         printf("ROLL: %d, PITCH: %d, YAW: %d\n", gyroRaw.roll, gyroRaw.pitch, gyroRaw.yaw);
//         printf("Current millis = %lu\n", millis());
        
//         boolean accel_readingValid = true;
// 
//         printf("\n----Accel---\n");
//         Accel_Attitude(&accelAttitude, &accel_readingValid);
//         printf("Roll: %d, Pitch: %d\n", accelAttitude.roll, accelAttitude.pitch);

        BEGIN_LOOP_1_FREQUENCY(100)
            IMU_Read(&attitude, lastRead);    
            lastRead = millis();
        END_LOOP_1_FREQUENCY(50)
                
        BEGIN_LOOP_2_FREQUENCY(1000)
            printf("Roll: %d, Pitch: %d, Yaw: %d\n", attitude.roll, attitude.pitch, attitude.yaw);
        END_LOOP_2_FREQUENCY(1000)
    }
    return 0;   /* never reached */
}
