/*
 *  LAB04 EXERCISE 2
 *  GROUP 6 - E/17/380, E/17/331
 */
#include <avr/io.h>
#include <util/delay.h>

#define DELAY 10

int main()
{
    DDRD |= (1 << 6); // sets PWM pin PD6 as output

    TCCR0A = (1 << WGM00) | (1 << WGM01);      // sets waveform generation mode to fast PWM
    TCCR0A |= (1 << COM0A1);    // sets to non inverting mode

    //TCCR0B |= (0 << WGM02); // sets waveform generation mode to fast PWM
    TCCR0B |= (1 << CS00) | (1 << CS01);  // sets the prescaler to 64

    int i;  // to save OCR0A value to vary the duty cycle

    while (1){
        for(i = 0; i < 256; i++){
            OCR0A = i;
            _delay_ms(DELAY);
        }
        for(i = 255; i >= 0; i--){
            OCR0A = i;
            _delay_ms(DELAY);
        }
    }

    return 0;
}
