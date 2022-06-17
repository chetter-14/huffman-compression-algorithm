#include <fstream>
#include <cstdint>
#include <map>
#include <queue>
#include <string>
#include <cstdint>
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
	std::cout << "The total number of symbols : " << charsCount << "\n";
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

void traverseTree(const HuffmanNode* node, std::string code, std::map< int, std::string>& encodingMap)
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
	std::cout << "The total number of chars (in encoding file) : " << charsAmount + 1 << "\n";
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
				{
					std::cout << "The total number of chars (in decoding file) : " << charsAmount << "\n";
					return;
				}
				charsAmount++;
				out << (char)ch;
				node = root;
			}
		}
	}
}

int main()
{
	// read a file and build characters' frequency table 
	std::ifstream fileToCompress;
	fileToCompress.open("input.txt", std::ios_base::binary);
	fileToCompress.unsetf(std::ios_base::skipws);

	std::map<int, int> frequencyTable = buildFrequencyTable(fileToCompress);

	// make a huffman tree
	HuffmanNode* root = buildEncodingTree(frequencyTable);
		
	// make huffman codes for each character
	std::map<int, std::string> encodingMap = buildEncodingMap(root);

	// write to compressed file (with huffman codes)
	std::ofstream compressedFileToWrite;
	compressedFileToWrite.open("compressed.txt", std::ios_base::binary);
	// compressedFileToWrite.unsetf(std::ios_base::skipws);
	fileToCompress.clear();
	fileToCompress.seekg(0, std::ios::beg);
	
	encodeData(fileToCompress, encodingMap, compressedFileToWrite);
	compressedFileToWrite.close();
	fileToCompress.close();

	// read from compressed file, translate to normal format and write to new file (decompress)
	std::ofstream decompressedFile;
	decompressedFile.open("decompressed.txt", std::ios_base::binary);
	decompressedFile.unsetf(std::ios_base::skipws);

	std::ifstream compressedFileToRead;
	compressedFileToRead.open("compressed.txt", std::ios_base::binary);

	decodeData(compressedFileToRead, root, decompressedFile);
	decompressedFile.close();
	compressedFileToRead.close();

	return 0;
}

