/*
 * CO321 - LAB07
 * EXERCICSE 3
 *
 * GROUP 06 :
 * E/17/331
 * E/17/380
 */

#include "eeprom.h"
#include <util/delay.h>
#include "keypad.c"
#include "lcd.c"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define DEFAULT_KEY 3
#define MAX 16

char *encrypt(char *message, int key){
    int i = 0;
    while (message[i])
    {
       if ((message[i] >= 'A') && (message[i] <= 'Z')) message[i] = 65 + (message[i] + key - 65) % 26;
        else if ((message[i] >= 'a') && (message[i] <= 'z')) message[i] = 97 + (message[i] + key - 97) % 26;
        i++;
    }
    return message;
}

int main(void)
{
    EEPROM_Write(0, DEFAULT_KEY);   // sets the default key
    
    lcd_init(LCD_DISP_ON);          // initialises the lcd
    lcd_clrscr();                   // clears the lcd screen
    lcd_puts("Caesar Cipher\n");   
    lcd_puts("Encryption\n");
    _delay_ms(2000);
    lcd_clrscr();
    _delay_ms(2000);

    while (1) {
        // prompts user to enter the plain text or change key
        lcd_puts("A - Encrypt\n");
        lcd_puts("B - Change key\n");
        
        char input = keyScan();     // scans for the input
        char c;

        if (input == 'B')
        {
            lcd_clrscr();                   // clears lcd
            lcd_puts("Enter a new key :\n");// prompts user to enter a new key
            lcd_command(LCD_DISP_ON_CURSOR);// turns on the cursor in lcd

            char key[8];                    // saves the key 
            int i = 0;                      // length of the entered integer

            do {
				c = keyScan();              // scans for input
				if (c == '*') {             // clears the previously entered input
					if (i > 0) {
						i--;
						lcd_gotoxy(i, 1);   // goes to (i,1) coordinate in lcd
						lcd_putc(' ');      // clears the character available
						lcd_gotoxy(i, 1);   // goes to (i,1) coordinate in lcd
					}
				}
				else if (c == 'A' || c == 'B' || c == 'C' || c == 'D') continue;    // ignores alphabetical values
				else if (c != '#' && i < 8) {                                       // saves input if # is not entered or length doesn't exceeds
					key[i++] = c;
					lcd_putc(c);
				}
			} while (c != '#' && i < 8);    // exits if # is entered or length exceeds

            key[i] = '\0';                  // adds the null terminator to the end
            int keyVal = atoi(key);         // converts the key to integer

            EEPROM_Write(0, keyVal);        // writes the key to the EEPROM

            lcd_command(LCD_DISP_ON);       // turns off the cursor
            lcd_clrscr();

            // displays the new key in the lcd
			lcd_puts("Key written to\n");
			lcd_puts("EEPROM.\n");
			_delay_ms(2000);
			lcd_clrscr();
			lcd_puts("New Key:\n");
			lcd_puts(key);
            _delay_ms(2000);
            lcd_clrscr();

        }

        else if (input == 'A')
        {
            lcd_clrscr();                           // clears lcd
            lcd_puts("Enter a new text :\n");       // prompts user to enter a new message
            lcd_command(LCD_DISP_ON_CURSOR);        // turns on the cursor in lcd

            char *message = (char *)malloc(sizeof(char) * MAX); // allocates memory for plain text message
            int i = 0;

            do {
				c = keyScan();                  // scans for input
				if (c == '*') {                 // clears the previously entered input
					if (i > 0) {
						i--;
						lcd_gotoxy(i, 1);       // goes to (i,1) coordinate in lcd
						lcd_putc(' ');          // clears the character available
						lcd_gotoxy(i, 1);       // goes to (i,1) coordinate in lcd
					}
				}
				else if (c != '#' && i < MAX) {
					message[i++] = c;
					lcd_putc(c);
				}
			} while (c != '#' && i < MAX);

			message[i] = '\0';                  // adds the null terminator to the end
            int key = EEPROM_Read(0);           // reads the key
            message = encrypt(message, key);

            lcd_command(LCD_DISP_ON);           // turns off the cursor
            lcd_clrscr();
			lcd_puts("Cipher text : \n");
			lcd_puts(message);
			_delay_ms(4000);
			lcd_clrscr();
        }
        
        
    }
}

