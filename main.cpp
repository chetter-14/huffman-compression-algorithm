#include <fstream>
#include <cstdint>
#include <map>
#include <queue>
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

int main()
{
	// read a file and build characters' frequency table 
	std::ifstream fileInput;
	fileInput.open("input.txt");

	std::map<int, int> frequencyTable = buildFrequencyTable(fileInput);

	// make a huffman tree
	HuffmanNode* root = buildEncodingTree(frequencyTable);
	
	std::cout << (char)root->getLeftChild()->getRightChild()->getChar() << " (char) : " << root->getLeftChild()->getRightChild()->getCount() << " (count)\n";

	return 0;
}

