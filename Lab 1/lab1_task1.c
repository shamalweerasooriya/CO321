/*
 *	E/17/380
 *	WEERASOORIYA S.S.
 *	LAB 1 - TASK 1
 *		* Connect four (4) LEDs to Port B and blink all of them simultaneously
 */

#include <avr/io.h>     // Standard avr Header
#include <util/delay.h> // Delay header

#define DELAY 200

int main(void)
{

    DDRB = DDRB | (0x0F); // Set pins 0-3 in PORTB as output pins

    // Infinite loop
    while (1)
    {
        PORTB = PORTB | 15; // Set the bits 0-3 to light up the LEDs
        _delay_ms(DELAY);   // Creates a timing delay
        PORTB = 0;          // Clear all the bits in PORTB
        //PORTB = PORTB & 0xF0; This can clear the bits 0-3 without inferring with the other bits
        _delay_ms(DELAY); // Creates a timing delay
    }
    return 0;
}