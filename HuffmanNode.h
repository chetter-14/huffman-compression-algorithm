#pragma once

#include <iostream>

constexpr int PSEUDO_EOF = 256;

class HuffmanNode {
	int character;					// character at this node
	int count;						// the frequency of the character
	const HuffmanNode* leftChild;			// left huffman child node
	const HuffmanNode* rightChild;			// right huffman child node

public:
	HuffmanNode() : character{}, count{ 0 }, leftChild{ nullptr }, rightChild{ nullptr } { }
	HuffmanNode(int c, int freq) : character{ c }, count{ freq }, leftChild{ nullptr }, rightChild{ nullptr } { }
	~HuffmanNode() {}

	int getChar() const { return character; }
	void setChar(int c) { character = c; }

	int getCount() const { return count; }
	void setCount(int c) { count = c; }

	const HuffmanNode* getLeftChild() const { return leftChild; }
	void setLeftChild(const HuffmanNode* node) { leftChild = node; }

	const HuffmanNode* getRightChild() const { return rightChild; }
	void setRightChild(const HuffmanNode* node) { rightChild = node; }
};


struct CmpHuffmanNodes
{
	bool operator()(const HuffmanNode* lhs, const HuffmanNode* rhs) const
	{
		return lhs->getCount() > rhs->getCount();
	}
};