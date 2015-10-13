#  modules_std_defs.mk

TOP := $(dir_noslash $(find_upwards main.c))
LIB := $(dir_noslash $(find_upwards rootFile))/lib

DEVICE = atmega328p
CLOCK = 16000000
FUSES = -U hfuse:w:0xde:m -U lfuse:w:0xff:m -U efuse:w:0x05:m

CC := avr-gcc
CFLAGS := -std=c99 -Os -Wall -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
PROGRAMMER := -c arduino -P $(shell ~/bin/get_serial)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(TOP) -I$(LIB) -c $(input) -o $(output)
