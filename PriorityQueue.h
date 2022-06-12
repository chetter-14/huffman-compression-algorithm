#pragma once

#include "Tree.h"

using namespace Tree;

constexpr int charsTableSize = 256;			// size of ASCII table


class PriorityQueue {

	Node** arr;
	int size;

public:
	PriorityQueue() : size{ 0 } { arr = new Node*[charsTableSize]; }
	~PriorityQueue() { delete[] arr; }

	int getSize() { return size; }

	void push(Node*);
	Node* pop();

	void display();
};