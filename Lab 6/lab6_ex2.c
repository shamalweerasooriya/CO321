/*
 * CO321 - LAB06
 * EXERCICSE 2
 *
 * GROUP 06 :
 * E/17/331
 * E/17/380
 */

#include <avr/io.h>

void usart_init(){
    /*
     * UMSEL01:0 = 00   // asynchronous USART
     * UPM01:0 = 00     // no parity
     * USBS0 = 0        // one stop bit
     * UCSZ01:0 = 11    // 8 bit parity
     */
    UCSR0C = 0b00000110;
    UBRR0L = 0x67;      // sets baud rate to 9600
}

void usart_send(char c){
    UCSR0B |= (1 << TXEN0);             // enables USART transmitter
    UDR0 = c;                           // writes the character byte to be transferred, to UDR0
    while (!(UCSR0A & (1 << UDRE0)));   // checks UDRE0 bit
}

char usart_receive(){
    UCSR0B |= (1 << RXEN0);             // enables USART receiver
    while (!(UCSR0A & (1 << RXC0)));    // checks RXC0 bit
    char c = UDR0;                      // received character
    return c;
}

// transmits a line of characters
void sendData(char line[]){
    int i = 0;
    while (line[i])                     // sends each char of the string until the end
    {
        usart_send(line[i++]);
    }
    usart_send('\n');                   // sends a new line char at end
}

int main(int argc, char const *argv[])
{   
    usart_init();                       // initialises the USART
    
    sendData("Shamal Weerasooriya E/17/380");
    sendData("Sathira Silva E/17/331");
    
    return 0;
}