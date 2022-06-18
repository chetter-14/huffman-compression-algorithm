#include <fstream>
#include <cstdint>
#include <map>
#include <queue>
#include <string>
#include <bitset>
#include "HuffmanNode.h"


// resource - https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1176/assn/huffman.html


std::map<int, int> buildFrequencyTable(std::istream& in)
{
	std::map<int, int> frequencyTable;		// key - character, value - frequency of that character

	int charsCount = 0;
	char ch;
	while (in >> ch)
	{
		charsCount++;
		if (frequencyTable.count(ch))
		{
			frequencyTable.find(ch)->second++;
			continue;
		}
		frequencyTable.insert(std::pair<int, int>(ch, 1));
	}
	frequencyTable.insert(std::pair<int, int>(PSEUDO_EOF, 1));
	return frequencyTable;
}

HuffmanNode* buildEncodingTree(std::map<int, int> freqTable)
{
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CmpHuffmanNodes > priorQueue;

	// fill the priority queue
	for (const auto& it : freqTable)
	{
		HuffmanNode* node = new HuffmanNode(it.first, it.second);
		priorQueue.push(node);
	}
	
	// form a huffman tree
	while (priorQueue.size() != 1)
	{
		const HuffmanNode* lastNode = priorQueue.top();
		priorQueue.pop();

		const HuffmanNode* preLastNode = priorQueue.top();
		priorQueue.pop();

		HuffmanNode* newNode = new HuffmanNode();
		newNode->setCount(lastNode->getCount() + preLastNode->getCount());
		newNode->setLeftChild(preLastNode);
		newNode->setRightChild(lastNode);

		priorQueue.push(newNode);
	} 

	return priorQueue.top();			// return a root
}

bool isLeaf(const HuffmanNode* node)
{
	return !(node->getLeftChild() || node->getRightChild());
}

void traverseTree(const HuffmanNode* node, std::string code, std::map<int, std::string>& encodingMap)
{
	if (node->getLeftChild())
	{
		traverseTree(node->getLeftChild(), code + "0", encodingMap);
	}
	if (node->getRightChild())
	{
		traverseTree(node->getRightChild(), code + "1", encodingMap);
	}
	if (isLeaf(node))
	{
		encodingMap.insert(std::pair<int, std::string>(node->getChar(), code));
	}
}

std::map<int, std::string> buildEncodingMap(const HuffmanNode* root)
{
	std::map<int, std::string> encodingMap;			// key - character, value - its huffman code
	traverseTree(root, "", encodingMap);
	return encodingMap;
}

void writeFrequencyTable(std::ofstream& out, std::map<int, int>& freqTable)
{
	out << '{';
	for (std::map<int,int>::iterator iter = freqTable.begin(); iter != freqTable.end(); iter++)
	{
		out << std::to_string(iter->first) << ':' << std::to_string(iter->second);
		if (iter != --freqTable.end())
		{
			out << ',';
		}
	}
	out << '}';
}

void encodeData(std::istream& in, const std::map<int, std::string>& encodingMap, std::ostream& out)
{
	int currByte = 0;
	int bitCount = 0;
	std::string charCode;

	int charsAmount = 0;

	// read char by char and write them into output file in bits
	char ch;


	while (in >> ch)
	{
		charsAmount++;
		charCode = encodingMap.find((int)ch)->second;
		std::cout << ch << " (char) : " << charCode << " (code)\n";
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
	charCode = encodingMap.find(PSEUDO_EOF)->second;
	for (int i = 0; i < charCode.size(); i++)
	{
		int bit = charCode.at(i) - '0';
		currByte = (currByte << 1) | bit;
		bitCount++;
		if (bitCount == BITS_IN_BYTE)
		{
			out << (char)currByte;
			currByte = 0;
			bitCount = 0;
		}
	}
	if (int bitsLeft = BITS_IN_BYTE - bitCount)
	{
		currByte = currByte << bitsLeft;
		out << (char)currByte;
	}
}

std::map<int, int> readFrequencyTable(std::ifstream& in)
{
	std::map<int, int> freqTable;
	
	bool isEnclosed = false;
	bool isKey = true, isValue = false;		// isKey - true because the map begins with the key
	std::string key, value;

	char ch;
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
			freqTable.insert(std::pair<int, int>( std::stoi(key), std::stoi(value) ));
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
	char byte;
	const HuffmanNode* node = root;

	int charsAmount = 0;

	while (in.read((char*)&byte, 1))
	{
		std::cout << std::bitset<8>(byte) << "\n";
		for (int i = BITS_IN_BYTE - 1; i >= 0; i--)
		{
			int bit = (byte >> i) & 0x1;
			if (bit)
			{
				node = node->getRightChild();
			}
			else
			{
				node = node->getLeftChild();
			}

			int ch = node->getChar();
			if (ch)
			{
				std::cout << (char)ch << "\n";
				if (ch == PSEUDO_EOF)
					return;

				charsAmount++;
				out << (char)ch;
				node = root;
			}
		}
	}
}

void compress(std::ifstream& in, std::ofstream& out)
{
	// make a frequency table
	std::map<int, int> frequencyTable = buildFrequencyTable(in);
	// make a huffman tree
	HuffmanNode* root = buildEncodingTree(frequencyTable);
	// make huffman codes for each character
	std::map<int, std::string> encodingMap = buildEncodingMap(root);
	// write to compressed file (with huffman codes
	in.clear();
	in.seekg(0, std::ios::beg);

	writeFrequencyTable(out, frequencyTable);
	encodeData(in, encodingMap, out);
}

void decompress(std::ifstream& in, std::ofstream& out)
{
	// read a frequency table from compressed file
	std::map<int, int> frequencyTable = readFrequencyTable(in);
	// build a tree based on that freq table
	HuffmanNode* root = buildEncodingTree(frequencyTable);
	decodeData(in, root, out);
}

int main()
{
	// FILE COMPRESSION 
	std::ifstream fileToCompress;
	fileToCompress.open("input.txt", std::ios_base::binary);
	fileToCompress.unsetf(std::ios_base::skipws);

	std::ofstream resultFile;
	resultFile.open("compressed.huf", std::ios_base::binary);

	compress(fileToCompress, resultFile);

	resultFile.close();
	fileToCompress.close();

	// FILE DECOMPRESSION
	std::ifstream compressedFile;
	compressedFile.open("compressed.huf", std::ios_base::binary);

	std::ofstream decompressedFile;
	decompressedFile.open("decompressed.txt", std::ios_base::binary);
	decompressedFile.unsetf(std::ios_base::skipws);

	decompress(compressedFile, decompressedFile);
	
	decompressedFile.close();
	compressedFile.close();

	return 0;
}

