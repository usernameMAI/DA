#include <string>
#include <iostream>

#ifndef LAB2_V2_BITS_H
#define LAB2_V2_BITS_H

const int NUMBER_OF_BITS_IN_A_BYTE = 8;
const int MAX_SHIFT = 7;

bool BitNumberIndexIsOne (const std::string& key, int index);
int FirstDifferenceInBit (const std::string& firstString, const std::string& secondString);

#endif //LAB2_V2_BITS_H
