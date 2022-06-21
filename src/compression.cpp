#include "compression.h"
#include "HuffmanNode.h"
#include "utils.h"
#include "ofbitstream.h"
#include <string>
#include <map>


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
	for (std::map<int, int>::iterator iter = freqTable.begin(); iter != freqTable.end(); iter++)
	{
		out << std::to_string(iter->first) << ':' << std::to_string(iter->second);

		if (iter != --freqTable.end())			// if not the last key-value pair in the map
			out << ',';
	}
	out << '}';
}

void encodeData(std::istream& in, const std::map<int, std::string>& encodingMap, std::ostream& out)
{
	std::string charCode;
	ofbitstream fileOutput{ out };

	// read char by char and write them into output file in bits
	unsigned char ch;
	while (in >> ch)
	{
		charCode = encodingMap.find((int)ch)->second;
		fileOutput.writeHuffmanCode(charCode);
	}

	charCode = encodingMap.find(PSEUDO_EOF)->second;
	fileOutput.writeHuffmanCode(charCode);

	fileOutput.writeLeftBits();		// if any bits are left (not full up to the byte) then fill the byte with zeros and write it
}

void compress(std::ifstream& in, std::ofstream& out)
{
	// make a frequency table
	std::map<int, int> frequencyTable = buildFrequencyTable(in);
	std::cout << "\tMade a frequency table.\n";

	// make a huffman tree
	HuffmanNode* root = buildEncodingTree(frequencyTable);
	std::cout << "\tBuilt an encoding tree (huffman tree).\n";

	// make huffman codes for each character
	std::map<int, std::string> encodingMap = buildEncodingMap(root);
	std::cout << "\tBuilt an encoding map (chars with appropriate codes).\n";

	// write to compressed file (with huffman codes
	in.clear();
	in.seekg(0, std::ios::beg);

	writeFrequencyTable(out, frequencyTable);
	encodeData(in, encodingMap, out);
	std::cout << "\tWrote codes to file.\n";

	freeTree(root);
}