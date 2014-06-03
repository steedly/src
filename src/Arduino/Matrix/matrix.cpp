#include "Arduino.h"
#include "max7219.h"

#define MAX_PATH 132

int main(void)
{
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	Serial.begin(9600);
	
	char string[MAX_PATH] = "3 2 1...Blastoff!!!  ";
	char buffer[MAX_PATH];
	int iBufferIdx = 0;
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
				delay(30); // display for 50ms
			}

			c1 = c2;
			c2 = string[++i];
			if( Serial.available() > 0)
			{
				char ch = Serial.read();
				Serial.print(ch);
				buffer[iBufferIdx++] = ch;
				if(iBufferIdx >= MAX_PATH-2 || ch == 13)
				{
					Serial.println("");
					// make null terminated string
					buffer[iBufferIdx++] = '\0';
					// Copy back into string
					memcpy(string, buffer, iBufferIdx);
					Serial.println(string);
					// Reset buffer length
					iBufferIdx = 0;
					break;
				}
			}
		}
	}
    
	return 0;
}
