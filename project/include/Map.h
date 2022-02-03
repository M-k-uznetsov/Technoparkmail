#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstddef>

#define ERROR -1

enum essense {
     NOTHING,
     WOLF,
     DOG,
     RAT,
     ARMOR,
     HELMET,
     SHIELD,
     PANTS,
     TSHIRT
};

class Map{
 private:
    size_t max_x;
    size_t max_y;
    std::vector<std::vector<size_t>> map;
 public:
    explicit Map(size_t _max_x = 0, size_t _max_y = 0);
    explicit Map(std::istream& is);
    std::vector<size_t>& operator[] (const size_t index);
    std::vector<size_t> operator[] (const size_t index) const;
    size_t get_max_y() const;
    size_t get_max_x() const;
};
