#include "Arduino.h"

void setup()
{
	pinMode(13,OUTPUT);
}

void loop()
{
	digitalWrite(13,HIGH);
	delay(1000);
	digitalWrite(13,LOW);
	delay(1000);
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
