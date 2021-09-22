/*
 *  LAB04 EXERCISE 3
 *  GROUP 6 - E/17/380, E/17/331
 */
#include <avr/io.h>
#include <util/delay.h>

#define DELAY 2000

int main()
{
    DDRD |= (1 << 6); // sets PWM pin PD6 as output

    TCCR0A = (1 << WGM00) | (1 << WGM01);      // sets waveform generation mode to fast PWM  
    TCCR0A |= (1 << COM0A1);    // sets to non inverting mode
    TCNT0 = 0x00;   // clears the timer counter register


    OCR0A = 0x7F;   // sets the duty cycle to 50%
    int i;  // to save the prescaler modes

    while (1){
        /*
         * Precaler     Frequency
         * 1            62.5kHz
         * 8            7.8125kHz
         * 64           976.5625Hz
         * 256          244.141Hz
         * 1024         61.035Hz
         */
        // sets different prescaler modes
        for (i = 5; i > 1; i--){
			TCCR0B = i;         // sets the prescaler / sets waveform generation mode to fast PWM   since WGM02 = 0
			_delay_ms(DELAY);			
		}
    }

    return 0;
}
