/*
 * CO321 - LAB06
 * EXERCICSE 3
 *
 * GROUP 06 :
 * E/17/331
 * E/17/380
 */

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
    UBRR0L = 0x67;
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
    while (line[i] != '\n')             // sends each char of the string until the end of line
    {
        usart_send(line[i++]);
    }
    usart_send('\n');                   // sends a new line char at end
}

// receives a line of characters
char * receiveData(){
    char *line = (char*)malloc(1000);   // to hold chars of the receiving line
    char c;
    int i = 0;
    while (1)                           // receives each char of the string until the end of line
    {
        c = usart_receive();
        if (c != '\n') line[i++] = c;
        else {line[i++] = '\n'; break;}
    }
    return line;
}

int main(int argc, char const *argv[])
{   
    usart_init();                       // initialises the USART
    char *line;
    while (1)
    {
        line = receiveData();           // receives a line of characters
        int i = 0;
        while (line[i])                 // implements caesar cipher until the end of line
        {
            if ((line[i] >= 'A') && (line[i] <= 'Z')) line[i] = 65 + (line[i] + 3 - 65) % 26;
            else if ((line[i] >= 'a') && (line[i] <= 'z')) line[i] = 97 + (line[i] + 3 - 97) % 26;
            i++;
        }
        sendData(line);                 // sends a line of characters
        free(line);
    }
    
    return 0;
}