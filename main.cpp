#include <fstream>
#include <cstdint>
#include <map>
#include <queue>
#include <string>
#include "HuffmanNode.h"


// resource - https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1176/assn/huffman.html


std::map<int, int> buildFrequencyTable(std::istream& in)
{
	std::map<int, int> frequencyTable;		// key - character, value - frequency of that character

	char ch;
	while (in >> ch)
	{
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

std::map<int, std::string> buildEncodingMap(const HuffmanNode* node, std::string code)
{
	std::map<int, std::string> encodingMap;			// key - character, value - its huffman code
	// std::cout << "Node count - " << node->getCount() << "\n";

	if (node->getLeftChild())
	{
		buildEncodingMap(node->getLeftChild(), code + "0");
	}
	if (node->getRightChild())
	{
		buildEncodingMap(node->getRightChild(), code + "1");
	}
	if (isLeaf(node))
	{
		encodingMap.insert(std::pair<int, std::string>(node->getChar(), code));
		std::cout << node->getChar() << " (char) : " << code << " (code)\n";
	}
	return encodingMap;
}

int main()
{
	// read a file and build characters' frequency table 
	std::ifstream fileInput;
	fileInput.open("input.txt");

	std::map<int, int> frequencyTable = buildFrequencyTable(fileInput);

	// make a huffman tree
	HuffmanNode* root = buildEncodingTree(frequencyTable);
		
	std::map<int, std::string> encodingMap = buildEncodingMap(root, "");

	for (const auto& it : encodingMap)
	{
		std::cout << it.first << " (char) : " << it.second << " (code)\n";
	}

	return 0;
}

