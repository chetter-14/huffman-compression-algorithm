#include "PriorityQueue.h"

//void PriorityQueue::push(HuffmanNode* node)
//{
//	
//	// put a new node into the correct position (priority queue in descending order by frequencies)
//	int in;
//	for (in = vect.size() - 1; in >= 0; in--)
//	{
//		if (vect[in]->getCount() < node->getCount())
//			vect[in + 1] = vect[in];
//		else
//			break;
//	}
//	vect[in + 1]
//}
//
//Node* PriorityQueue::pop()
//{
//	return arr[--size];
//}
//
//void PriorityQueue::display()
//{
//	for (int i = 0; i < size; i++)
//	{
//		arr[i]->display(std::cout);
//		std::cout << "\n";
//	}
//}