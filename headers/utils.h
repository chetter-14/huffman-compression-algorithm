#ifndef _UTILS_H
#define _UTILS_H

#include <map>
#include <fstream>
#include <queue>
#include "HuffmanNode.h"

constexpr int BITS_IN_BYTE = 8;

std::map<int, int> buildFrequencyTable(std::istream& in);
HuffmanNode* buildEncodingTree(std::map<int, int> freqTable);
void freeTree(const HuffmanNode* node);

#endif
