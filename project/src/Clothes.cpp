#include <cstddef>
#include "Clothes.h"

Clothes::Clothes() {
    avaible.resize(NUMBER_OF_THINGS);
    for (size_t i = 0; i < NUMBER_OF_THINGS ; ++i) {
        avaible[i] = false;
    }
}

std::vector<bool>::reference Clothes::operator[] (const size_t index) {
    return avaible[index];
}

bool Clothes::operator[] (const size_t index) const {
    return avaible[index];
}

