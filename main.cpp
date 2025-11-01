#include <avr/io.h>
#include <util/delay.h>

static int PATTERN[] = {
	0x13e,
	0x102,
	0x37,
	0x117,
	0x10b,
	0x11d,
	0x13d,
	0x106,
	0x13f,
	0x11f,
	0x12f,
	0x139,
	0x3c,
	0x133,
	0x3d,
	0x2d
};

void outputPattern(int digit, int ix) {
	int val = PATTERN[ix];
	PORTB_OUT = val & 0x3f;

	int dmask = digit == 0 ? 0x02 : 0x04;
	PORTC_OUT = ((val >> 8) & 0x01)	// last segment
		| dmask
		;
}

void off() {
	PORTC_OUT = 0x6;
}

void outputNumber(int val) {
	outputPattern(0, val & 0xf);
	for(int i = 0; i < 100; i++)
		;
	PORTC_OUT = 0x6;
	outputPattern(1, (val >> 4) & 0xf);
	for(int i = 0; i < 100; i++)
		;
	PORTC_OUT = 0x6;
}

int loop() {
	int v = PORTA_IN;
	outputNumber(v);
	_delay_us(5);
}

int main() {
	PORTA_DIR = 0x00;					// All inputs

	//-- Enable pull-up resistors on port A pins (hex input)
	PORTA_PIN0CTRL = 0x08;				// Enable pull-up
	PORTA_PIN1CTRL = 0x08;				// Enable pull-up
	PORTA_PIN2CTRL = 0x08;				// Enable pull-up
	PORTA_PIN3CTRL = 0x08;				// Enable pull-up
	PORTA_PIN4CTRL = 0x08;				// Enable pull-up
	PORTA_PIN5CTRL = 0x08;				// Enable pull-up
	PORTA_PIN6CTRL = 0x08;				// Enable pull-up
	PORTA_PIN7CTRL = 0x08;				// Enable pull-up

	PORTC_DIR = 0xff;
	PORTB_DIR = 0xff;
	PORTB_OUT = 0x00;					// All segments off
	PORTC_OUT = 0x06;					// C segment off, common cathodes HIGH

	for(;;) {
		loop();
	}
}


