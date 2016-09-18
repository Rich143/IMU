# IMU

Code to read an IMU sensor consisting of an acceleremoter, magnetometer and gyroscope.
Calculates the orientation of the sensor.

Reads the Accelerometer, Gyroscope, and Magnetometer over I2C, and applies a complementary filter to the data to obtain an attitude reading consisting of roll, pitch and yaw angles.

Uses the I2C and UART Drivers from the repository Rich143/AVR-Lib
