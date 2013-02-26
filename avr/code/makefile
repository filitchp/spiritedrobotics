#
# Makefile for the avr board of the Santa Barbot
#   Written by Ryan Bahneman
#

# Flags
CC=avr-gcc
TARGET=atmega328
OP=-Os # Optimization
PROGRAMMER=avrispmkii 

# builds the firmware with out downloading it. run 'make program' to download the file
fw: firmware.hex

# Download the program
program: firmware.hex
	sudo avrdude -c$(PROGRAMMER) -p $(TARGET) -P usb -U flash:w:firmware.hex

# Firmware Binary
firmware.hex: firmware.elf
	avr-objcopy -j .text -j .data -O ihex firmware.elf firmware.hex

# Firmware
firmware.elf: hello_world.o led_strip.o motor_driver.o communication.o
	$(CC) -s -mmcu=$(TARGET) $(OP) hello_world.o led_strip.o motor_driver.o -o firmware.elf

# Source
hello_world.o: hello_world.c led_strip.h
	$(CC) -c -mmcu=$(TARGET) $(OP) hello_world.c

led_strip.o: led_strip.c led_strip.h
	$(CC) -c -mmcu=$(TARGET) $(OP) led_strip.c

motor_driver.o: motor_driver.c motor_driver.h
	$(CC) -c -mmcu=$(TARGET) $(OP) motor_driver.c

communication.o: communication.c communication.h
	$(CC) -c -mmcu=$(TARGET) $(OP) communication.c

# Clean
clean:
	rm -f *.o *.elf *.hex

# Hex
read_fuses:
	sudo avrdude -U hfuse:r:high.hex:i -c$(PROGRAMMER) -p $(TARGET) -P usb
	sudo avrdude -U lfuse:r:low.hex:i  -c$(PROGRAMMER) -p $(TARGET) -P usb



