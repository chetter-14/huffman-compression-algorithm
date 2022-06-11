#pragma once

class Codeword {

	unsigned int code_size;		// codeword may take up to 32 bits, so we take care of its size 
								// i.e 0b0000...0001 (so where should we start? code_size tells us about it)
	int codeword;				// i.e. 0b011
	char ch;

public:

	Codeword() : code_size{ 0 } { }

	char getChar() { return ch; }
	void setChar(char c) { ch = c; }



	void addZero() 
	{ 
		codeword << 1; 
	}

	void addOne()
	{
		(codeword << 1) | 0b1;
	}
};