#include "PriorityQueue.h"

void PriorityQueue::push(Node* node)
{
	if (size == 0)
	{
		arr[size] = *node;
	}
	else 
	{
		// put a new node into the correct position (priority queue in descending order by frequencies)
		int in;
		for (in = size - 1; in >= 0; in--)
		{
			if (arr[in].getFreq() < node->getFreq())
				arr[in + 1] = arr[in];
			else
				break;
		}
		arr[in + 1] = *node;
	}
	size++;
}

Node& PriorityQueue::pop()
{
	return arr[--size];
}

void PriorityQueue::display()
{
	for (int i = 0; i < size; i++)
	{
		arr[i].display(std::cout);
		std::cout << "\n";
	}
}