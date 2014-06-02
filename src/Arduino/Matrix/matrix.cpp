#include "Arduino.h"
#include "max7219.h"

int main(void)
{
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	const char string[] = "3 2 1...Blastoff!!!  ";
	max7219 displayDriver;

	for(;;)
	{
		// Go through string we want to display
		int i=0;
		int c1=' ';
		int c2=string[i];
		while( c2 != 0 )  // still old PBASIC style completely asking for a buffer overrun--need to clean up 
		{
			//const SCode &code = g_codeTable[character];
			for( int j=0; j<9; j++ )
			{
				displayDriver.Display8x8Font(c1,c2,j);
				delay(50); // display for 50ms
			}

			c1 = c2;
			c2 = string[++i];
		}
	}
    
	return 0;
}
