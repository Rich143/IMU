IMPLICIT_DEPS=../lib/libs.aaccelerometer/accelerometer.ogyroscope/gyroscope.oimu.omagnetometer/magnetometer.omain.otimer/timer.o
CWD=.
META_DEPS=/usr/local/crosspack-avr-20131216/bin/avr-gcc
IMPLICIT_TARGETS=program.elf
SORTED_DEPS=accelerometer/accelerometer.o/usr/local/crosspack-avr-20131216/bin/avr-gccgyroscope/gyroscope.oimu.o../lib/libs.amagnetometer/magnetometer.omain.otimer/timer.o
SIG_METHOD_NAME=C
BUILD_SIGNATURE=1444776646,19308
INCLUDE_SFXS=lib.la.so.sa.a.sl
COMMAND=avr-gcc -std=c99 -Wall -Os -DF_CPU=16000000 -mmcu=atmega328p -I. -I../lib -o program.elf main.o imu.o timer/timer.o accelerometer/accelerometer.o gyroscope/gyroscope.o magnetometer/magnetometer.o ../lib/libs.a
ARCH=darwin-thread-multi-2level
DEP_SIGS=1444776646,29441387211187,6027561444776646,16681444776646,31321444680856,109521444776646,15561444776646,19201444776646,1188
SIG_METHOD_IMPLICIT=1
INCLUDE_PATHS=lib/usr/local/lib/usr/libsys.../lib/usr/local/include/usr/includeuser.../lib/usr/local/include/usr/include
SIGNATURE=1444776646,19308
END=