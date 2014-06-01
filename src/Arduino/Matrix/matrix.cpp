#include "Arduino.h"
#include "max7219.h"

int main(void)
{
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	const char codeList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0};
	max7219 displayDriver;

	for(;;)
	{
		// Go through string we want to display
		int i=0;
		int codeIdx=codeList[i];
		while( codeIdx != 0 )  // still old PBASIC style completely asking for a buffer overrun--need to clean up 
		{
			const SCode &code = g_codeTable[codeIdx];
			displayDriver.DisplayMatrix(code);
			delay(200); // display for 200ms
			codeIdx=codeList[++i];
		}
	}
    
	return 0;
}
