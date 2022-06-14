#include <fstream>
#include <cstdint>
#include <map>
#include <queue>
#include "HuffmanNode.h"
#include "PriorityQueue.h"


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

void buildEncodingTree(std::map<int, int> freqTable)
{
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CmpHuffmanNodes > priorQueue;

	for (const auto& it : freqTable)
	{
		HuffmanNode* node = new HuffmanNode(it.first, it.second);
		priorQueue.push(node);
	}
	
	while (priorQueue.size())
	{
		const HuffmanNode* lastNode = priorQueue.top();
		std::cout << lastNode->getChar() << " (char) : " << lastNode->getCount() << " (count)\n";
		priorQueue.pop();
	} 
}


int main()
{
	// read a file and build characters' frequency table 
	std::ifstream fileInput;
	fileInput.open("input.txt");

	std::map<int, int> frequencyTable = buildFrequencyTable(fileInput);

	buildEncodingTree(frequencyTable);

	return 0;
}

