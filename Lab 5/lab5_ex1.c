/*
 * CO321 - LAB05
 * EXERCICSE 1
 *
 * GROUP 06 :
 * E/17/380
 * E/17/331
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {

	DDRC &= ~(1<<1);    // sets ADC1 as an input pin 			
	DDRD = 0xFF;        // sets all the pins in PORTD as output pins
    /*
     * ADCSRA configuration
     * ADEN = 1 : enables ADC
     * ADPS2:0 = 111 : sets the prescaler to 128
     */
	ADCSRA = 0b10000111;
    /*
     * ADMUX configuration
     * REFS1:0 = 01 : sets AVCC as Vref
     * MUX3:0 = 0001 : selects ADC1 as the input channel
     * ADLAR = 0 : justifies to right
     */
    ADMUX = 0b01000001;

    int v, volts;   // to save Dout and corresponding voltage

	while(1){

		ADCSRA |= (1<<ADSC);    //  starts conversion

		while(ADCSRA & (1<<ADIF)==0)    // polls until ADIF bit sets
        PORTD = 0;

		v = (int)ADCL + (int)(ADCH<<8); // calculates Dout

		if (v > 920) volts = 31;        // Vin >= 4.5 : voltage = 5
        else if (v > 716) volts = 15;   // 4.5 > Vin >= 3.5 : voltage = 4
        else if (v > 512) volts = 7;    // 3.5 > Vin >= 2.5 : voltage = 3
        else if (v > 307) volts = 3;    // 2.5 > Vin >= 1.5 : voltage = 2
        else if (v > 102) volts = 1;    // 1.5 > Vin >= 0.5 : voltage = 1
        else  volts = 0;                // 0.5 >  : voltage = 0

        PORTD = volts;  // sets the voltage as PORTD's output

		ADCSRA |= (1<<ADIF);    // restarts the conversion	

	}

	return 0;
}
