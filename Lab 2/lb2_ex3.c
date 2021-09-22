/*
 * E/17/380
 * Weerasooriya S.S
 *
 * Extend the program in part 2, so that the number of times the push button was 
 * released is displayed as a binary number on a set of LEDs connected to PORTB.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

static int x = 0; // static integer saves the no of times the push button was released

int main()
{

    DDRD &= ~(1 << 2); // sets PD2 (INT0) as input
    DDRD |= (1 << 7);  // sets PD7 as output (signal for the LED)
    DDRB = 0x3F;       // sets PD0-PD5 as outputs

    EICRA |= (1 << ISC01);  // sets for falling edge detetcion
    EICRA &= ~(1 << ISC00); // sets for falling edge detection

    sei(); // enables global interrupts (sets bit 7 of SREG)

    EIMSK |= (1 << INT0); // enables external interrupt for INT0

    PORTD &= ~(1 << 7); // clears PD7 initially

    while (1)
    {
    }
    return 0;
}

// Defining ISR
ISR(INT0_vect)
{
    PORTD ^= (1 << 7); // toggles PD7 at each interrupt
    PORTB = ++x;       // increments and assigns the no of releases to PORTB
}