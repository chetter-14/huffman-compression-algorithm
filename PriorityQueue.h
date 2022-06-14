#pragma once

#include <vector>
#include "HuffmanNode.h"


class PriorityQueue {

	std::vector<HuffmanNode*> vect;

public:
	PriorityQueue() { }
	~PriorityQueue() { vect.clear(); }

	int getSize() { return vect.size(); }

	void push(HuffmanNode*);
	HuffmanNode* pop();

	void display();
};