#pragma once

struct SCode
{
public:
	char code[8];
	const char& operator [](int idx) const
	{
		return code[idx];
	}
};

const char NumberOfCodes = 22;
const SCode g_codeTable[NumberOfCodes] = {
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01100000,
		0b01100000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01100000,
		0b01100000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01100000,
		0b01100000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b01100000,
		0b01100000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b01100000,
		0b01100000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b01100000,
		0b01100000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b01100000,
		0b01100000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00110000,
		0b00110000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00011000,
		0b00011000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001100,
		0b00001100
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000110,
		0b00000110
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000011,
		0b00000011
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000001,
		0b00000001
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	}
	/*
	{
	 '%11111111,
	 '%11111111,
	 '%11000011,
	 '%11000011,
	 '%11000011,
	 '%11000011,
	 '%11111111,
	 '%11111111
	},
	{
	 '%00011000,
	 '%00111000,
	 '%00011000,
	 '%00011000,
	 '%00011000,
	 '%00011000,
	 '%11111111,
	 '%11111111
	},
	{
	 '%11111111,
	 '%11111111,
	 '%11111111,
	 '%11111111,
	 '%11111111,
	 '%11111111,
	 '%11111111,
	 '%11111111
	}
	*/
};
			  
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
		
		SetRegister(0xC, 0x1);	// Set normal operation
		SetRegister(0x9, 0x0);	// Set decode mode
		SetRegister(0xB, 0x7);	// Set scan limit
		SetRegister(0xF, 0x0);	// Set Display-Test Register to normal mode
	}
	void SetRegister(char address, char val)
	{
		// clock in register
		digitalWrite(CS,LOW);		// LOW CS
		digitalWrite(CLK,LOW);		// LOW CLK

		shiftOut(DIN, CLK, 1, val);
		shiftOut(DIN, CLK, 1, address);
		// load the register

		// PULSOUT CS, 1
		digitalWrite(CS,HIGH);
		digitalWrite(CS,LOW);

		// DEBUG "Code: ", BIN8 code, " Register: ", BIN16 ShiftRegisterData, CR
		printf("Code: %x Register: %x\n", val, address);

		return;
	}

	void DisplayMatrix(const SCode &c, bool debug=false)
	{
		if(!debug)
		{
			for( int i=0; i<MatrixHeight; i++ )
				SetRegister(i+1, c[i]);
		}
		else
		{
			char mask = 1 << 7;
			for( int i=0; i<MatrixWidth; i++ )
			{
				if( mask & c[i] )
					printf("*");
				else
					printf(" ");
				mask = mask >> 1;
			}
		}

		return;
	}
 
};

