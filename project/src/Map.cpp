#include <iostream>
#include <vector>
#include <cstddef>

#include "Map.h"

Map::Map(size_t _max_x, size_t _max_y)
    :max_x(_max_x)
    , max_y(_max_y) {
    map.resize(max_x, std::vector<size_t>(max_y));
}
Map::Map(std::istream& is) {
    is >> max_x >> max_y;
    map.resize(max_x, std::vector<size_t>(max_y));
    size_t i, j;
    while (is) {
        is >> i >> j;
        std::string enemy_name;
        is >> enemy_name;
        if (enemy_name.compare("wolf") == 0) {
            map[i][j] = WOLF;
        } else if (enemy_name.compare("dog") == 0) {
            map[i][j] = DOG;
        } else if (enemy_name.compare("rat") == 0) {
            map[i][j] = RAT;
        } else if (enemy_name.compare("armor") == 0) {
            map[i][j] = ARMOR;
        } else if (enemy_name.compare("helmet") == 0) {
            map[i][j] = HELMET;
        } else if (enemy_name.compare("shield") == 0) {
            map[i][j] = SHIELD;
        } else if (enemy_name.compare("pants") == 0) {
            map[i][j] = PANTS;
        } else if (enemy_name.compare("T-Shirt") == 0) {
            map[i][j] = TSHIRT;
        }
    }
}

std::vector<size_t>& Map::operator[] (const size_t index) {
    return map[index];
}
std::vector<size_t> Map::operator[] (const size_t index) const {
    return map[index];
}
size_t Map:: get_max_y() const {
    return max_y;
}

size_t Map::get_max_x() const {
    return max_x;
}
