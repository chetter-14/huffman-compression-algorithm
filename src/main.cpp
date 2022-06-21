#include "compression.h"
#include "decompression.h"
#include <fstream>
#include <iostream>


// resource - https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1176/assn/huffman.html

int main()
{
	// FILE COMPRESSION 
	std::cout << "Begin compression!\n";

	std::ifstream fileToCompress;
	fileToCompress.open("A_Tour_of_C_Second_Edition_2018_Stroustrup_B.pdf", std::ios_base::binary);	// here we specify the file to be compressed
	fileToCompress.unsetf(std::ios_base::skipws);

	std::ofstream resultFile;
	resultFile.open("compressed.huf", std::ios_base::binary);

	compress(fileToCompress, resultFile);
	resultFile.close();
	fileToCompress.close();

	std::cout << "Compression is done!\n\n";

	// FILE DECOMPRESSION
	std::cout << "Begin decompression!\n";

	std::ifstream compressedFile;
	compressedFile.open("compressed.huf", std::ios_base::binary);

	std::ofstream decompressedFile;
	decompressedFile.open("decompressed.pdf", std::ios_base::binary);
	decompressedFile.unsetf(std::ios_base::skipws);

	decompress(compressedFile, decompressedFile);
	
	decompressedFile.close();
	compressedFile.close();

	std::cout << "Decompression is done!\n";

	return 0;
}

