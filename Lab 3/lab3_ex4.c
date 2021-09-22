/*
    Group 6

    Calculating the initial counter value:
    XTAL = 16MHz ---> T = 1/16000 ms
    Since the maximum delay that can be achieved using TIMER0 is 16.384ms,
    We will use TIMER1.
    Choose prescaling as 1:1024.
    T after pre-scaling = 1024 / 16000
    Therefore 1s ---> 16000 * 1000 / 1024 = 15625 ticks.
    TCNT1 = 1 + 65535 - 15625 = 49911.

    Compilation and burning:
    avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p ex4.c -o ex4
    avr-objcopy -O ihex -R .eeprom ex4 ex4.hex
    avrdude -F -V -c arduino -p ATMEGA328P -P COM5 -b 115200 -U flash:w:ex4.hex
*/

// Defined to allow variable delay for the delay() function.
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Definition of the used pins for knight rider circuit (Pin 0-3 in port B)
#define _PB0 1	// (1 << 0)
#define _PB1 2	// (1 << 1)
#define _PB2 4	// (1 << 2)
#define _PB3 8	// (1 << 3)
#define ALL 15	// (1 << 4) - 1  <---- Bit mask for all pins from 0 to 3

// Period of the knight-rider is 1s
#define BLINK_DELAY_MS 83.3333

// Function to blink some set of pins in a specific PORT with some delay.
void blink(volatile uint8_t *PORT, uint8_t pins, int delay) {
    // Set the pins in the PORT to HIGH
	*PORT |= pins;
    // Wait
    _delay_ms(delay);
    // Set the pins in the PORT to LOW
    *PORT &= ~pins;
    // Wait
    _delay_ms(delay);
}

// ISR for TIMER1 Overflow Interrupt
ISR (TIMER1_OVF_vect) {
    PORTB ^= (1 << 5);                  // Toggle pin PB5
    TCNT1 = 49911;                      // Reload the timer/counter register.
}

int main() {
    DDRB |= (1 << 5);                   // Configure pin PB5 as output.
    DDRB |= ALL;                        // Configure PB0-3 pins to serve as Outputs.

    TCNT1 = 49911;                      // Load the timer/counter register.

    TCCR1A = 0x00;                      // Set the timer under normal mode.
    TCCR1B = (1 << CS10) | (1 << CS12); // Prescaling enabled with 1:1024.
    TIMSK1 = (1 << TOIE1);              // Enable timer1 overflow interrupt (TOIE1).

    sei();                              // Enable global interrupts by setting global interrupt enable bit in SREG.

    // The blinking sequence for one iteration
    uint8_t sequence[] = {_PB3, _PB2, _PB1, _PB0, _PB1, _PB2};

    while (1)
        for (int i = 0; i < 6; i++) 
            blink(&PORTB, sequence[i], BLINK_DELAY_MS);
}