#include <avr/io.h>

void delay_timer0() {
    /*
    *XTAL = 16MHz → Txtal _clock = 1/16  µs 
    *Prescaler = 1:256 → Tcounter_clock = 256 × 1/16  µs = 16µs 
    *Counter increments needed = 4ms / 16µs = 250 increments 
    *Initial counter value = 1+255 – 250 = 6
    */

    TCNT0 = 6;          // Load the timer/counter register with 6.

    TCCR0A = 0x00;      // Set the timer under normal mode.
    TCCR0B = 0x04;      // Prescaling enabled with 1:256
    // Wait until the timer/counter register overflows (TOV0 will be 1)
    while ((TIFR0 & 0x01) == 0);

    // Clear the timer settings.
    TCCR0A = 0x00;
    TCCR0B = 0x00;

    TIFR0 = 0x01;       // Clear the TOV0 bit by manually writting 1.
}

int main() {
    DDRB |= (1 << 5);       // Configure pin PB5 as output.
	//TIMSK0 |= 0x01;
  
    while (1) {
      	for (int i = 0; i < 125; i++)
      		delay_timer0();
        PORTB ^= (1 << 5);  // Toggle pin PB5
    }
}