#pragma once
#include <iostream>

namespace Tree
{
	class Node {

		char ch;
		int frequency;
		Node* leftChild;		// left child node
		Node* rightChild;		// right child node

	public:
		Node() : ch{}, frequency{ 0 }, leftChild{ nullptr }, rightChild{ nullptr } { }
		Node(char c, int freq) : ch{ c }, frequency{ freq }, leftChild{ nullptr }, rightChild{ nullptr } { }
		~Node() {}

		char getChar() { return ch; }
		void setChar(char c) { ch = c; }

		int getFreq() { return frequency; }
		void setFreq(int freq) { frequency = freq; }

		Node* getLeftChild() { return leftChild; }
		void setLeftChild(Node* node) { leftChild = node; }

		Node* getRightChild() { return rightChild; }
		void setRightChild(Node* node) { rightChild = node; }

		void display(std::ostream&);

		void addLeftChild(Node* node) { leftChild = node; }
		void addRightChild(Node* node) { rightChild = node; }

		Node operator+(Node& node);
	};
}
