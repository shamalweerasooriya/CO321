#include <avr/io.h>
#include <stdlib.h>

void usart_init(){
    /*
     * UMSEL01:0 = 00   // asynchronous USART
     * UPM01:0 = 00     // no parity
     * USBS0 = 0        // one stop bit
     * UCSZ01:0 = 11    // 8 bit parity
     */
    UCSR0C = 0b00000110;
    UBRR0L = 0x67;      // sets baud rate to 9600
    UCSR0B |= (1 << RXEN0);             // enables USART receiver
    UCSR0B |= (1 << TXEN0);             // enables USART transmitter
}

void usart_send(char c){
    UDR0 = c;                           // writes the character byte to be transferred, to UDR0
    while (!(UCSR0A & (1 << UDRE0)));   // checks UDRE0 bit
}

char usart_receive(){
    while (!(UCSR0A & (1 << RXC0)));    // checks RXC0 bit
    char c = UDR0;                      // received character
    return c;
}

// transmits a line of characters
void usart_sendString(char line[]){
    int i = 0;
    while (line[i])                     // sends each char of the string until the end
    {
        usart_send(line[i++]);
    }
    usart_send('\n');                   // sends a new line char at end
    usart_send('\0');
}

char * usart_receiveString(){
    char *line = (char*)malloc(1000);   // to hold chars of the receiving line
    char c;
    int i = 0;
    while (1)                           // receives each char of the string until the end of line
    {
        c = usart_receive();
        if (c == '\r' || c == '\n' || c == '\0') break;
        // usart_send(c);
        line[i++] = c;
    }
    line[i] = '\0';
    return line;
}