/*
 *	E/17/380
 *	WEERASOORIYA S.S.
 *	LAB 1 - TASK 2
 *		* Using four (4) LEDs, implement a "Knight Rider" style display
 */

#include <avr/io.h>     // Standard avr Header
#include <util/delay.h> // Delay header

#define DELAY 200

int main(void)
{

    DDRB = DDRB | (0x1E); // Set pins 1-4 in PORTB as output pins
    int x = 1;            // int value that determines which way to move
    int i;                // increment value that sets the direction of movement (left if 1, right if 4)

    // Infinite loop
    while (1)
    {
        if (x == 4) // Sets the movement to left
            i = -1;
        else if (x == 1) // Sets the movement to right
            i = 1;

        PORTB = PORTB | (1 << x);  // Sets a single bit to light up the LED
        _delay_ms(DELAY);          // Creats a timing delay
        PORTB = PORTB & ~(1 << x); // Clears the single bit that was set previously

        x = x + i; // Increments or decrements x value
    }
    return 0;
}
