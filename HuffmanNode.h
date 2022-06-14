#pragma once

#include <iostream>

constexpr int PSEUDO_EOF = 256;

class HuffmanNode {
	int character;					// character at this node
	int count;						// the frequency of the character
	HuffmanNode* leftChild;			// left huffman child node
	HuffmanNode* rightChild;		// right huffman child node

public:
	HuffmanNode() : character{}, count{ 0 }, leftChild{ nullptr }, rightChild{ nullptr } { }
	HuffmanNode(char c, int freq) : character{ c }, count{ freq }, leftChild{ nullptr }, rightChild{ nullptr } { }
	~HuffmanNode() {}

	int getChar() const { return character; }
	void setChar(int c) { character = c; }

	int getCount() const { return count; }
	void setCount(int c) { count = c; }

	HuffmanNode* getLeftChild() const { return leftChild; }
	void setLeftChild(HuffmanNode* node) { leftChild = node; }

	HuffmanNode* getRightChild() const { return rightChild; }
	void setRightChild(HuffmanNode* node) { rightChild = node; }

	void display(std::ostream& out);
};


struct CmpHuffmanNodes
{
	bool operator()(const HuffmanNode* lhs, const HuffmanNode* rhs) const
	{
		return lhs->getCount() > rhs->getCount();
	}
};