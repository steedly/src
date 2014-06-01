#include "Arduino.h"

void setup()
{
	pinMode(13,OUTPUT);
}

void loop()
{
	digitalWrite(13,HIGH);
	delay(200);
	digitalWrite(13,LOW);
	delay(200);
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
