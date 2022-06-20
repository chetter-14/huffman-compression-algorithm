#ifndef _UTILS_H
#define _UTILS_H

#include <map>
#include <fstream>
#include <queue>
#include "HuffmanNode.h"


std::map<int, int> buildFrequencyTable(std::istream& in);
HuffmanNode* buildEncodingTree(std::map<int, int> freqTable);

#endif
