#include "Arduino.h"
#include <stdio.h>
#include "matrix_code.h"

void setup()
{
	printf("LED matrix driver\n");

	const char codeList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0};
	max7219 displayDriver;

	delay(200); // display for 200ms
	// Go through string we want to display
	for( char intensity = 0; intensity<=0xF; intensity++ )
	{
		printf("setting intensity to %d\n", intensity);
		displayDriver.SetRegister(0xA, intensity); // Set intensity
		int i=0;
		int codeIdx=codeList[i];
		while( codeIdx != 0 )  // still old PBASIC style completely asking for a buffer overrun--need to clean up 
		{
			const SCode &code = g_codeTable[codeIdx];
			displayDriver.DisplayMatrix(code,true);
		}
	}
}

void loop()
{
}

int main(void)
{
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
	}
        
	return 0;
}
