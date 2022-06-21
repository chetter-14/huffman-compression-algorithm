#include "decompression.h"
#include "HuffmanNode.h"
#include "utils.h"
#include <map>
#include <string>
#include <iostream>


std::map<int, int> readFrequencyTable(std::ifstream& in)
{
	std::map<int, int> freqTable;

	bool isEnclosed = false;
	bool isKey = true, isValue = false;		// isKey - true because the map begins with the key
	std::string key, value;

	unsigned char ch;
	while (in.read((char*)&ch, 1))
	{
		switch (ch)
		{
		case '{':
			break;

		case '}':
			isEnclosed = true;
			freqTable.insert(std::pair<int, int>(std::stoi(key), std::stoi(value)));
			return freqTable;

		case ':':
			isValue = true;
			isKey = false;
			break;

		case ',':
			isKey = true;
			isValue = false;
			freqTable.insert(std::pair<int, int>(std::stoi(key), std::stoi(value)));
			key = ""; value = "";
			break;

		default:
			if (isKey)
				key += ch;
			if (isValue)
				value += ch;
			break;
		}
	}
	if (!isEnclosed)
	{
		std::cout << "Failed to read frequency table!\n";
	}
	return freqTable;
}

void decodeData(std::istream& in, const HuffmanNode* root, std::ostream& out)
{
	unsigned char byte;
	const HuffmanNode* node = root;

	int charsRead = 0;

	while (in.read((char*)&byte, 1))
	{
		for (int i = BITS_IN_BYTE - 1; i >= 0; i--)
		{
			int bit = (byte >> i) & 0x1;
			if (bit)
				node = node->getRightChild();
			else
				node = node->getLeftChild();

			int ch = node->getChar();
			if (node->doesHasChar())
			{
				if (ch == PSEUDO_EOF)
					return;

				out << (unsigned char)ch;
				node = root;
			}
		}
	}
}


void decompress(std::ifstream& in, std::ofstream& out)
{
	// read a frequency table from compressed file
	std::map<int, int> frequencyTable = readFrequencyTable(in);
	std::cout << "\tRead a frequency table from file header.\n";

	// build a tree based on that freq table
	HuffmanNode* root = buildEncodingTree(frequencyTable);
	std::cout << "\tBuilt an encoding tree (huffman tree).\n";
	decodeData(in, root, out);
	std::cout << "\tRead compressed file data, wrote to a new one in a 'readable' format.\n";

	freeTree(root);
}