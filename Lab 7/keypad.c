#include <avr/io.h>
#include <util/delay.h>


#define KEYPAD_PORT 	PORTD
#define KEYPAD_DDR		DDRD
#define KEYPAD_PIN		PIND

char keypad[4][4] = {{'1', '2', '3', 'A'},
							  {'4', '5', '6', 'B'},
							  {'7', '8', '9', 'C'},
							  {'*', '0', '#', 'D'}};

unsigned char colloc, rowloc;

char keyScan()
{
	unsigned char colloc, rowloc;

	while (1) {
		KEYPAD_DDR = 0xF0;						// Pins D0-D3 are set as inputs (columns). D4-D7 are set as outputs (rows).
		KEYPAD_PORT = 0xFF;						// Rows are initially set to HIGH. Internal pull-ups are enabled for column inputs.
												// Therefore, the column pins are at HIGH when no key is pressed.

		// If a key is pressed, read the column status and wait for it to be released.
		do {
			KEYPAD_PORT &= 0x0F; 				// Mask PORT for column read only.
			asm("NOP");
			colloc = (KEYPAD_PIN & 0x0F);		// Read status of columns.
		} while (colloc != 0x0F);				// Wait for a key to be released.

		// Handle debouncing.
		do {
			do {
				_delay_ms(20);				  	// 20ms key debounce time.
				colloc = (KEYPAD_PIN & 0x0F); 	// Read status of column.
			} while (colloc == 0x0F);		  	// Check for any key press.

			_delay_ms(20); 						// 20 ms key debounce time.
			colloc = (KEYPAD_PIN & 0x0F);
		} while (colloc == 0x0F);

		// Now check for rows.
		// Check for pressed key in 0th row.
		KEYPAD_PORT = 0x7F;						// Set D7 to LOW.
		asm("NOP");
		colloc = (KEYPAD_PIN & 0x0F);
		if (colloc != 0x0F) {
			rowloc = 0;
			break;
		}

		// Check for pressed key in 1st row.
		KEYPAD_PORT = 0xBF;						// Set D6 to LOW.
		asm("NOP");
		colloc = (KEYPAD_PIN & 0x0F);
		if (colloc != 0x0F) {
			rowloc = 1;
			break;
		}

		// Check for pressed key in 2nd row.
		KEYPAD_PORT = 0xDF;						// Set D5 to LOW.
		asm("NOP");
		colloc = (KEYPAD_PIN & 0x0F);
		if (colloc != 0x0F) {
			rowloc = 2;
			break;
		}

		// Check for pressed key in 3rd row.
		KEYPAD_PORT = 0xEF;						// Set D4 to LOW.
		asm("NOP");
		colloc = (KEYPAD_PIN & 0x0F);
		if (colloc != 0x0F) {
			rowloc = 3;
			break;
		}
	}

	if (colloc == 0x07)							// Columns: 0111
		return (keypad[rowloc][0]);
	else if (colloc == 0x0B)					// Columns: 1011
		return (keypad[rowloc][1]);
	else if (colloc == 0x0D)					// Columns: 1101
		return (keypad[rowloc][2]);
	else										// Columns: 0011
		return (keypad[rowloc][3]);
}