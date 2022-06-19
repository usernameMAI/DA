#include "bits.hpp"

bool BitNumberIndexIsOne (const std::string& key, int index){
    int indexElementInKey = index / NUMBER_OF_BITS_IN_A_BYTE;
    if (indexElementInKey >= key.size()) {
        return false;
    }
    char checkElement = key[indexElementInKey];
    int idxBit = (MAX_SHIFT - index % NUMBER_OF_BITS_IN_A_BYTE);
    return (checkElement & (1 << idxBit));
}

int FirstDifferenceInBit (const std::string& firstString, const std::string& secondString) {
//    функция ищет первый несовпадающий бит, работает только для не одинаковых строк!!
    int maxCountBits = std::max(firstString.size(), secondString.size()) * NUMBER_OF_BITS_IN_A_BYTE;
    for (int i = 0; i < maxCountBits; ++i) {
        if (BitNumberIndexIsOne(firstString, i) != BitNumberIndexIsOne(secondString, i)) {
            return i;
        }
    }
    std::cout << "Function FirstDifferenceInBit called with identical strings.\n";
    exit(1);
}
