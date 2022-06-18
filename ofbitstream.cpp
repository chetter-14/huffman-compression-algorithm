#include "ofbitstream.h"


void ofbitstream::writeHuffmanCode(const std::string& charCode)
{
	for (int i = 0; i < charCode.size(); i++)
	{
		int bit = charCode.at(i) - '0';
		currByte = currByte << 1 | bit;
		bitCount++;
		if (bitCount == BITS_IN_BYTE)
		{
			out << (char)currByte;
			currByte = 0;
			bitCount = 0;
		}
	}
}

void ofbitstream::writeLeftBits()
{
	if (int bitsLeft = BITS_IN_BYTE - bitCount)
	{
		currByte = currByte << bitsLeft;
		out << (char)currByte;
	}
}
