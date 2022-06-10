#include "Tree.h"

using namespace Tree;

void Node::display(std::ostream& out)
{
	out << "char " << ch << " and frequency - " << frequency;
}

Node Node::operator+(Node& node)
{
	Node newNode{};
	newNode.setFreq(frequency + node.getFreq());
	newNode.setLeftChild(this);
	newNode.setRightChild(&node);

	return newNode;
}