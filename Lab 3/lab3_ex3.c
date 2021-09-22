/*
    Group 6

    Calculating the maximum possible generated delay using TIMER0:
    XTAL = 16MHz ---> T = 1/16000 ms
    The maximum count that can be counted in TIMER0 is 256.
    Therefore when the smallest prescaling value is used,
    Maximum delay = (256 x 1024 / 16000)ms = 16.384ms.
*/

#include <avr/io.h>

void delay_timer0() {
    TCNT0 = 0;          // Load the timer/counter register with 0.

    TCCR0A = 0x00;      // Set the timer under normal mode.
    TCCR0B = 0x05;      // Prescaling enabled with 1:1024

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