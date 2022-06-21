#ifndef UTILS_H
#define UTILS_H

#include "HuffmanNode.h"
#include <map>
#include <fstream>

constexpr int BITS_IN_BYTE = 8;

std::map<int, int> buildFrequencyTable(std::istream& in);
HuffmanNode* buildEncodingTree(std::map<int, int> freqTable);
void freeTree(const HuffmanNode* node);

#endif
