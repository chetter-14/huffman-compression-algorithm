#include "utils.h"
#include <queue>


std::map<int, int> buildFrequencyTable(std::istream& in)
{
	std::map<int, int> frequencyTable;		// key - character, value - frequency of that character
	unsigned char ch;
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
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CmpHuffmanNodes> priorQueue;

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

void freeTree(const HuffmanNode* node)
{
	if (node->getLeftChild())
		freeTree(node->getLeftChild());

	if (node->getRightChild())
		freeTree(node->getRightChild());

	node->~HuffmanNode();
}
