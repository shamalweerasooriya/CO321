/*
 * E/17/380
 * Weerasooriya S.S
 *
 * Write a program that toggles pin PB0 (show using a connected LED)
 * whenever the push button is released, using external interrupts.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{

    DDRD &= ~(1 << 2); // sets PD2 (INT0) as input
    DDRB |= (1 << 0);  // sets PB0 as output

    EICRA |= (1 << ISC01);  // sets for falling edge detetcion
    EICRA &= ~(1 << ISC00); // sets for falling edge detection

    sei(); // enables global interrupts (sets bit 7 of SREG)

    EIMSK |= (1 << INT0); // enables external interrupt for INT0

    PORTB &= ~(1 << 0); // clears PB0 initially

    while (1)
    {
    }
    return 0;
}

// Defining ISR
ISR(INT0_vect)
{
    PORTB ^= (1 << 0); // toggles PB0 at each interrupt
}