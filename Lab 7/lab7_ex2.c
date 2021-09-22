/*
 * CO321 - LAB07
 * EXERCICSE 2
 *
 * GROUP 06 :
 * E/17/331
 * E/17/380
 */

#include "eeprom.h"
#include "usart.h"
#include <util/delay.h>

int main(int argc, char const *argv[])
{
    usart_init();   // initialises usart

    char *buff;     // buffer to save a string

    // loops infinitely
    while (1)
    {
        usart_sendString("Select operation (w - WRITE, r - READ)"); // prompts the user to select an option

        char input = usart_receive();                               // receives the user input character
        usart_receive();                                            // receives the carriage return charatcter
        
        // EEPROM write option
        if (input == 'w')
        {
            usart_sendString("Enter an input string");              // prompts the user to enter an input string
            buff = usart_receiveString();                           // receives the input string
            EEPROM_WriteString(0, buff);                            // writes the string to the EEPROM
            usart_sendString("Successfully written to EEPROM!");    // reports the user on successful write operation to EEPROM
            free(buff);                                             // free up space in buffer
        }
        // EEPROM read operation
        else if (input == 'r'){
            buff = EEPROM_ReadString(0, 1024);                      // reads the first 1024 bytes in EEPROM
            usart_sendString(buff);                                 // sends the string to the serial monitor
            free(buff);                                             // // free up space in buffer
        }
        // invalid input
        else{
            usart_sendString("Error : invalid input");
        }
    }
    

    return 0;
}
