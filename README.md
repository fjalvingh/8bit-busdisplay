# 8-bit hex bus display board

This should become a small display board which can be used to show the 8-bit
value on some bus on a 2 digit 7-segment display. The board uses an ATTINY1616
microcontroller which is dirt cheap and has 18 I/O pins. I need 9 for the display
(7x for a segment, 2x for selecting the digit) and 8 for input, so there's one
pin left which I will use to enable latching of the value if so desired.

I prototyped the thingy on a breadboard:

![breadboard prototype](breadboard.png)



