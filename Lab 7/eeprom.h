#include <avr/io.h>
#include <stdlib.h>

// writes a single byte to the given EERPROM address
void EEPROM_Write(unsigned int addr, char data){
    while (EECR & (1 << EEPE));             // waits until the previous write is complete
    
    EEAR = addr;                            // sets address
    EEDR = data;                            // sets data register

    EECR |= (1 << EEMPE);                   // enables write globally

    EECR |= (1 << EEPE);                    // starts EEPROM write
}

// reads a single byte at the given address of the EEPROM
char EEPROM_Read(unsigned int addr){
    while (EECR & (1 << EEPE));             // waits until the previous write is complete
    
    EEAR = addr;                            // sets address 
    EECR |= (1 << EERE);                    // starts EEPROM read
    return EEDR;                            // returns data
}

// writes a string of data to EEPROM starting from the given address
void EEPROM_WriteString(unsigned int addr, char *string){
    while (*string)  EEPROM_Write(addr++, *string++);
    // int i = 0;
    // while (string[i])
    // {
    //     EEPROM_Write(addr++, string[i++]);
    // }
    
}

// reads n bytes of data starting from the given address
char * EEPROM_ReadString(unsigned int addr, int n){
    char *buffer = (char*)malloc(1024);     // holds the data read from EEPROM
    char c;                                 // holds a single byte read from EEPROM
    int i = 0;

    // reads all the n bytes saved in EEPROM
    while (n--)
    {
        c = EEPROM_Read(addr++);            // reads a single byte at the current address of the EEPROM
        if (c == '\r' || c == '\n') break;  // is this necessary ?
        buffer[i++] = c;                    // saves it on the buffer
    }

    //buffer[i] = '\0';                     // adds null terminal character at the end
    return buffer;                          // returns the buffer
    
}