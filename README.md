# 8-bit hex bus display board

WORK IN PROGRESS, USE AT YOUR OWN RISK!

This should become a small display board which can be used to show the 8-bit
value on some bus on a 2 digit 7-segment display. The board uses an ATTINY1616
microcontroller which is dirt cheap and has 18 I/O pins. I need 9 for the display
(7x for a segment, 2x for selecting the digit) and 8 for input, so there's one
pin left which I will use to enable latching of the value if so desired.

I prototyped the thingy on a breadboard:

![breadboard prototype](breadboard.png)

## Installing the prerequisite software (Linux/Ubuntu)

I do not use Windows (I hate and detest Microsof) so for that you're on your own. I followed the instructions from here: [https://michael-crum.com/attiny1616/], many thanks to Michael!

Basically, you do:

```
sudo apt update
sudo apt install gcc-avr binutils-avr avr-libc gdb-avr avrdude
```
This should allow you to build the code with the usual 'make' command. This will do a build and also attempt to update the attiny using UPDI.

For that I used an USB to RS232 (5V) adapter and the following schematic:

![UDPI using a serial adapter](udpiserial.png)

* Red and black are the 5V pins from the Serial adapter
* White is the RX pin from the serial adapter
* Green is the TX pin from the serial adapter
* The resistor is 1K.

Once built you can test whether it can connect to the chip as follows:

```
sudo avrdude -c serialupdi -p t1616 -P "/dev/ttyUSB0" -b 57600
```
which should answer something like:
```
avrdude: AVR device initialized and ready to accept instructions
avrdude: device signature = 0x1e9421 (probably t1616)
```

## The schematic

Made in Kicad, the schematic diagram is very simple:

![Schematic](schematic.png)

and the PCB is tiny:

![PCB](pcb.png)

The boards are on order from China, waiting for them to arrive to test the design.