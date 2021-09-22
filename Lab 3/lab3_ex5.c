#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count = 0;    // overflow count

void delay_timer0(){
    TCNT0 = 0x96;   // Load the timer/counter register with 150

    TCCR0A = 0x00;  // Set the timer under normal mode
    TCCR0B = 0x04;  // Prescaling enabled with 1:256

    TIMSK0 |= (1 << TOIE0); // enables timer counter overflow interrupt

    sei();  // enables global interrupts (sets bit 7 of SREG)

    while (1);
    
}

// defining ISR
ISR(TIMER0_OVF_vect){
    // restarts the delay when it stops
    if (count++ > 24)
    {
        PORTB ^= (1<<5);    // toggles pin PB5 of PORTB
        count = 0;          // sets back to 0 to restart the delay
        TCNT0 = 0x96;       // Load the timer/counter register with 150 to restart the delay
    }
    
}

int main(){
    DDRB |= (1 << 5); // Configure pin PB5 as output.

    delay_timer0();
}