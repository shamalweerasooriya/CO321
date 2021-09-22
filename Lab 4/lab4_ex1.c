/*
 *  LAB04 EXERCISE 1
 *  GROUP 6 - E/17/380, E/17/331
 */
#include <avr/io.h>

int main()
{
    DDRD |= (1 << 6); // sets PWM pin PD6 as output

    TCCR0A = (1 << WGM00) | (1 << WGM01);      // sets waveform generation mode to fast PWM
    TCCR0A |= (1 << COM0A1);    // sets to non inverting mode
    
    //TCCR0B |= (0 << WGM02); // sets waveform generation mode to fast PWM
    TCCR0B = 0x03;  // sets the prescaler to 64

    OCR0A = 0x7F;   // sets the duty cycle to 50%

    while (1);

    return 0;
}
