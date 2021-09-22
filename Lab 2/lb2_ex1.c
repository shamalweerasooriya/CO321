/*
 * E/17/380
 * Weerasooriya S.S
 *
 * PD7 pin is connected to a push button. Write a program that uses 6 LEDs connected to 
 * PORTB (6 LSBs) to display the number of times the push button is pressed, as a binary 
 * number. Implement without using external interrupts. (i.e. Use polling)
 */

#include <avr/io.h>
#include <util/delay.h>

int main()
{

    DDRB |= (0x3F);    // set pins 0-5 in PORTB as output
    DDRD &= ~(1 << 7); // sets PD7 as input

    int x = 1;     // no of times the push button has been pushed
    int state = 0; // state of the input (to detect the rising and falling edges)

    while (1)
    {
        // polling for the input at PD7
        while ((PIND >> 7) & 1)
        {
            PORTB = x; // sets the no of pushes as the output of PORTB
            state = 1; // changes the state to 1 (after detecting the rising edge)
        }
        // polling for the falling edge at PD7
        if ((~(PIND >> 7) & 1) && state)
        {
            ++x;       // increments the no of pushes
            state = 0; // changes the state to 0 (after detecting the faliing edge)
        }
    }

    return 0;
}