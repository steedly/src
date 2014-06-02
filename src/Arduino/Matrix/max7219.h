#pragma once
#include "matrix_code.h"

#define FONT_8x8
#include "font.h"

struct max7219
{
private:
	// Pin connections
	static const char DIN=8;	// Connected to P8
	static const char CS=7;		// Connected to P7
	static const char CLK=6;	// Connected to P6
	static const char MatrixWidth=8;
	static const char MatrixHeight=8;
public:

	max7219()
	{
		pinMode(DIN, OUTPUT);
		pinMode(CS, OUTPUT);
		pinMode(CLK, OUTPUT);
		SetRegister(0xC, 0x1);	// Set normal operation
		SetRegister(0x9, 0x0);	// Set decode mode
		SetRegister(0xB, 0x7);	// Set scan limit
		SetRegister(0xF, 0x0);	// Set Display-Test Register to normal mode
		SetRegister(0xA, 0x7);	// Set intensity
	}
	void SetRegister(char address, char val, bool bMSBFirst=true)
	{
		// initialize clock and clock select
		digitalWrite(CS,LOW);		// LOW CS
		digitalWrite(CLK,LOW);		// LOW CLK

		// clock in register
		shiftOut(DIN, CLK, 1, address);
		shiftOut(DIN, CLK, bMSBFirst ? 1 : 0, val);

		// PULSOUT CS, 1
		digitalWrite(CS,HIGH);
		digitalWrite(CS,LOW);

		return;
	}
	void Display8x8Font(const char character1, const char character2, int pos)
	{
		if( pos < 0 || pos > 8 )
			pos = 0;
		const uint8_t *c1 = font_8x8[character1-32];
		const uint8_t *c2 = font_8x8[character2-32];
		for( int i=pos; i<8; i++ )
			SetRegister(i+1-pos, c1[i], false);
		if( pos > 0 )
			SetRegister(8+1-pos, 0x0, false);
		for( int i=0; i<pos-1; i++ )
			SetRegister(i+8+1-pos+1, c2[i], false);

		return;
	}
	void Display8x8Font(const char character)
	{
		const uint8_t *c = font_8x8[character-32];
		for( int i=0; i<8; i++ )
			SetRegister(i+1, c[i], false);

		return;
	}
	void DisplayMatrix(const SCode &c)
	{
		for( int i=0; i<MatrixHeight; i++ )
			SetRegister(i+1, c[i], true);

		return;
	}
 
};
