// outputFileBitStream - write to file a data in bits
// the buffer in size of 1 byte is used for this

#ifndef OFBITSTREAM_H
#define OFBITSTREAM_H

#include <iostream>

constexpr int BITS_IN_BYTE = 8;

class ofbitstream {

	int currByte;
	int bitCount;
	std::ostream& out;

public:
	ofbitstream(std::ostream& o) : out(o), currByte{ 0 }, bitCount{ 0 } { }
	~ofbitstream(){ }

	void writeHuffmanCode(const std::string&);
	void writeLeftBits();
};

#endif