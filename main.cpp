#include <fstream>
#include "PriorityQueue.h"

int charsCodewords[charsTableSize];


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
	while (priorQueue.getSize() != 1)
	{
		Node& lowestNode1 = priorQueue.pop();
		Node& lowestNode2 = priorQueue.pop();

		Node newNode = lowestNode1 + lowestNode2;
		priorQueue.push(newNode);
	}
}

int goLeftChild(Node& node)
{
	int codeword = 
}

void goRightChild(Node& node)
{
	
}

void generate_code(Node& node)
{
	int codeword;
	goLeftChild(*node.getLeftChild());
	goRightChild(*node.getRightChild());
}

int main()
{
	int charsFreqsArr[charsTableSize]{};			// an array of characters frequencies
	
	count_frequency(charsFreqsArr);

	PriorityQueue priorQueue;

	// assign values 
	for (int i = 0; i < charsTableSize; i++)
		priorQueue.push( Node((char)i, charsFreqsArr[i]) );

	make_huffman_code(priorQueue);

	int charsCodewords[charsTableSize]{};
	generate_code(priorQueue.pop());

	priorQueue.display();

	return 0;
}


