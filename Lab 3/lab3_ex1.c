/*
    Group 6

    Calculating the initial counter value:
    XTAL = 16MHz ---> T = 1/16000 ms
    Choose prescaling as 1:256
    T after prescaling = 256/16000 ms = 0.016ms
    Therefore 2ms ---> 2ms / 0.016ms = 125 clocks
    TCNT0 = 1 + 255 - 125 = 131
*/

#include <avr/io.h>

void delay_timer0() {
    TCNT0 = 131;        // Load the timer/counter register with: 1 + 255 - 2 / (256 / 16000)

    TCCR0A = 0x00;      // Set the timer under normal mode.
    TCCR0B = 0x04;      // Prescaling enabled with 1:256

    // Wait until the timer/counter register overflows (TOV0 will be 1)
    while (!(TIFR0 & 0x01));

    // Clear the timer settings.
    TCCR0A = 0x00;
    TCCR0B = 0x00;

    TIFR0 = 0x01;       // Clear the TOV0 bit by manually writting 1.
}

int main() {
    DDRB |= (1 << 5);       // Configure pin PB5 as output.

    while (1) {
        delay_timer0();
        PORTB ^= (1 << 5);  // Toggle pin PB5
    }
}