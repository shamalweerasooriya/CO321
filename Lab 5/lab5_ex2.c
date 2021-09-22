/*
 * CO321 - LAB05
 * EXERCICSE 2
 *
 * GROUP 06 :
 * E/17/331
 * E/17/380
 */

#include <avr/io.h>
#include <util/delay.h>

#define THRESH 700

// The following function initializes the ADC.
void initADC() {
    DDRC = 0x00;                                            // Make ADC port as input.
    ADCSRA = (1 << ADEN);                                   // Enable the ADC module.
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);   // Set the ADC prescaler to 128.
    ADMUX = 0x00;                                           // Select the AVCC pin as the reference, MUX bits are set to 0 which selects the channel 0 by default.
                                                            // ADC result is right-justified as ADLAR is not set (default).
}

// The following function reads the ADC value given the channel.
int readADC(int channel) {
    ADMUX &= ~0x0f;                                         // Clear the MUX bits.
    ADMUX |= channel;                                       // Select the channel.
    ADCSRA |= (1 << ADSC);                                  // Start the conversion.
    while (ADCSRA & (1 << ADIF) == 0);                      // Wait for the conversion to complete by polling the ADIF bit.
    return ((int) ADCH) * 256 + (int) ADCL;                 // Read the result.
}

int main() {
    initADC();                                              // Initialize the ADC.
    _delay_ms(50);                                          // Wait for the ADC to stabilize.
    DDRB = 0x01;                                            // Set PB0 as output.
    int value;

    while (1) {
        value = readADC(1);                                 // Read the ADC value for channel 0.
        if (value > THRESH) PORTB = 0x01;                   // If the ADC value is less than THRESH, set the output pin high.
        else PORTB = 0x00;                                  // Else, set the output pin low.
    }

    return 0;
}