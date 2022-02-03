#pragma once

#include <cstddef>

class Enemy{
 private:
    int hp;
    size_t basic_dmg;
    size_t weapon;
 public:
    explicit Enemy(int _hp = 0, size_t _basic_dmg = 0,
                   size_t _wearpon = 0);
    void kick(size_t dammage = 0);
    int get_hp() const;
    size_t get_dmg() const;
};
