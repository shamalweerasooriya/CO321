/*
 * E/17/380
 * Weerasooriya S.S
 *
 * Connect two push buttons (A and B) to two external interrupt pins. Connect
 * 6 LEDs to a GPIO port. Write a program where a user can input a binary number
 * using the two push buttons (press A to input a '0', press B to input a '1')
 * through external interrupts, and display that number using the LEDs. 
 * The number must be updated and displayed every time one of the buttons 
 * are pressed.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

static int x = 0; // number to be displayed

int main()
{

    DDRD &= ~(0x0C); // sets PD2 (INT0) and PD3 (INT1) as input
    DDRB = 0x3F;     // sets PD0-PD5 as outputs

    EICRA |= (1 << ISC01);  // sets for falling edge detetcion for INT0
    EICRA &= ~(1 << ISC00); // sets for falling edge detection for INT0

    EICRA |= (1 << ISC11);  // sets for falling edge detetcion for INT1
    EICRA &= ~(1 << ISC10); // sets for falling edge detection for INT1

    sei(); // enables global interrupts (sets bit 7 of SREG)

    EIMSK |= (1 << INT0); // enables external interrupt for INT0
    EIMSK |= (1 << INT1); // enables external interrupt for INT1

    while (1)
    {
    }

    return 0;
}

// defining ISR for input B (1)
ISR(INT1_vect)
{
    PORTB = ++(x <<= 1); // shifts x to left by 1, sets LSB of x to 1, sets PORTB output to x
}

// defining ISR for input A (0)
ISR(INT0_vect)
{
    PORTB = (x <<= 1); // shifts x to left by 1, sets PORTB output to x
}