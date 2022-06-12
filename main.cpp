#include <fstream>
#include <cstdint>
#include "PriorityQueue.h"

int charsCodewords[charsTableSize]{};


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

Node* addNodes(Node* node1, Node* node2)
{
	Node* newNode = new Node{};
	newNode->setFreq(node1->getFreq() + node2->getFreq());
	newNode->setLeftChild(node1);
	newNode->setRightChild(node2);
	return newNode;
}

void make_huffman_tree(PriorityQueue& priorQueue)
{
	while (priorQueue.getSize() != 1)
	{
		Node* lowestNode1 = priorQueue.pop();
		Node* lowestNode2 = priorQueue.pop();

		Node* newNode = addNodes(lowestNode2, lowestNode1);
		priorQueue.push(newNode);
	}
}

bool is_leaf(Node* node)
{
	return !(node->getLeftChild() || node->getRightChild());
}

void print_code(std::ostream& out, int binCodeArr[], int level)
{
	for (int i = 0; i < level; i++)
		out << binCodeArr[i];
}

void generate_code(Node* node, int binCodeArr[], int count)
{
	// look at https://www.programiz.com/dsa/huffman-coding
	// and https://github.com/AshishYUO/huffman-compression/blob/master/huff.cpp 
	// for better understanding and further advancement

	if (node->getLeftChild())
	{
		binCodeArr[count] = 0;
		generate_code(node->getLeftChild(), binCodeArr, count + 1);
	} 
	if (node->getRightChild())
	{
		binCodeArr[count] = 1;
		generate_code(node->getRightChild(), binCodeArr, count + 1);
	}
	if (is_leaf(node))
	{
		if (node->getFreq() != 0) 
		{
			std::cout << node->getChar() << " : ";
			print_code(std::cout, binCodeArr, count);
			std::cout << "\n";
		}
	}
}

int main()
{
	int charsFreqsArr[charsTableSize]{};			// an array of characters frequencies
	
	count_frequency(charsFreqsArr);

	PriorityQueue priorQueue;

	// assign values 
	for (int i = 0; i < charsTableSize; i++)
		priorQueue.push( new Node((char)i, charsFreqsArr[i]) );

	priorQueue.display();

	make_huffman_tree(priorQueue);

	int binCodeArr[charsTableSize];					// charsTableSize - maximum height for huffman tree
	int count = 0;
	generate_code(priorQueue.pop(), binCodeArr, count);

	return 0;
}


