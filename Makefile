# Define variables that may change between projects
FILENAME = main
PORT = /dev/ttyUSB0
DEVICE = attiny1616
PROGRAMMER = serialupdi

# Clock speed must be provided for delays to be timed properly 
CLOCK = 20000000

# Baud rate for programming
BAUD = 115200

# Compile with options:
# - All warnings (-Wall)
# - Optimized for size (-0s)
# - Targeted to our mcu (-mmcu)
# - F_CPU defined as our clock speed (-DF_CPU)
COMPILE = avr-gcc -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(CLOCK)

default: compile upload clean

# Compile step
# file.cpp -> file.o -> file.elf -> file.hex
# Then print out the size of the binary
compile:
	$(COMPILE) -c $(FILENAME).cpp -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size $(FILENAME).elf

# Upload step
# Flash the .hex file onto the chip
upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

# Remove intermediate files
clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex

# Fuses are non-volatile settings that can be set by avrdude and persist between resets
# Setting fuse2 to 0x7e enables 20Mhz clock
# See page 34 of https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny1614-16-17-DataSheet-DS40002204A.pdf
fuse:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U fuse2:w:0x7e:m

