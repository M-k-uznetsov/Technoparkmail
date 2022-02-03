#pragma once

#include <iostream>
#include <cstddef>

#include"Enemy.h"

class Hero: public Enemy{
 private:
    size_t x;
    size_t y;
    size_t wgt;
    size_t arm;
 public:
    explicit Hero(int _hp = 100, size_t _basic_dmg = 0,
                  size_t _weapon = 1, size_t _x = 0,
                  size_t _y = 0, size_t _wgt = 0, size_t _arm = 0);
    void go_up();
    void go_down();
    void go_left();
    void go_right();
    size_t get_x() const;
    size_t get_y() const;
    size_t get_wgt() const;
    size_t get_arm() const;
    void set_wgt(size_t _wgt);
    void set_arm(size_t arm);
    void kick_arm(size_t dammage);
};
