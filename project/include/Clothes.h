#pragma once

#include<vector>
#include <cstddef>

#define ARMORWGT 3
#define ARMORARM 3
#define HELMETWGT 2
#define HELMETARM 3
#define SHIELDWGT 7
#define SHIELDARM 5
#define PANTSWGT 1
#define PANTSARM 1
#define TSHIRTWGT 1
#define TSHIRTARM 1
#define NUMBER_OF_THINGS 6

class Clothes{
 private:
    std::vector<bool> avaible;
 public:
    Clothes();
    std::vector<bool>::reference operator[] (const size_t index);
    bool operator[] (const size_t index) const;
};
