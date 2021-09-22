#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count = 0;    // overflow count

void delay_timer(){
    TCNT0 = 0xCB;   // Load the timer/counter register 0 with 203

    TCCR0A = 0x00;  // Sets  timer0 under normal mode
    TCCR0B = 0x04;  // Prescaling enabled in timer0 with 1:256

    TIMSK0 |= (1 << TOIE0); // enables timer counter overflow interrupt for timer0
    
    TCNT1 = 0x85EE; // Load the timer/counter register 1 with 34286

    TCCR1A = 0x00;  // Sets  timer1 under normal mode
    TCCR1B = 0x04;  // Prescaling enabled in timer1 with 1:256

    TIMSK1 |= (1 << TOIE0); // enables timer counter overflow interrupt for timer1

    sei();  // enables global interrupts (sets bit 7 of SREG)

    while (1);
    
}

// defines ISR fot timer0
ISR(TIMER0_OVF_vect){
    // restarts the delay when it stops
    if (count++ > 12)
    {
        PORTB ^= (1<<5);    // toggles pin PB5 of PORTB
        count = 0;          // sets back to 0 to restart the delay
        TCNT0 = 0xCB;       // Load the timer/counter register 0 with 203 to restart the delay
    }
    
}

// defines ISR fot timer1
ISR(TIMER1_OVF_vect){
    PORTB ^= (1<<4);    // toggles pin PB4 of PORTB
    TCNT1 = 0x85EE;     // Load the timer/counter register 0 with 34286 to restart the delay
}

int main(){
    DDRB |= (1 << 5) | (1 << 4);    // configure pin PB4 and PB5 as output.
    PORTB |= (0 << 5) | (0 << 4);   // clear bits in pin PB4 and PB5 

    delay_timer();
}