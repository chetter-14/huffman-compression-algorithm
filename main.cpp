#include <fstream>
#include "PriorityQueue.h"


void count_frequency(int* charsFreqsArr)
{
	std::ifstream inputFile;
	inputFile.open("input.txt");

	char ch;
	while (inputFile >> ch)
	{
		(*(charsFreqsArr + (int)ch))++;			// increment the count of the specified character
	}
}

void make_huffman_code(PriorityQueue& priorQueue)
{
	while (priorQueue.getSize() != 0)
	{
		Node& lowestNode1 = priorQueue.pop();
		Node& lowestNode2 = priorQueue.pop();

		Node newNode = lowestNode1 + lowestNode2;
		priorQueue.push(newNode);
	}
}

int main()
{
	int charsFreqsArr[charsTableSize]{};			// an array of characters frequencies
	
	count_frequency(charsFreqsArr);

	PriorityQueue priorQueue;

	// assign values 
	for (int i = 0; i < charsTableSize; i++)
		priorQueue.push( Node((char)i, charsFreqsArr[i]) );

	priorQueue.display();

	return 0;
}


