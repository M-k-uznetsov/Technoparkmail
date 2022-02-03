#include<iostream>
#include <cstddef>

#include "Enemy.h"
#include "Hero.h"


Hero::Hero(int _hp, size_t _basic_dmg,
           size_t _weapon, size_t _x,
           size_t _y, size_t _wgt, size_t _arm) :
                 Enemy(_hp, _basic_dmg, _weapon),
                 x(_x), y(_y),
                 wgt(_wgt), arm(_arm) {}

void Hero::go_up() {
    y += 1;
}

void Hero::go_down() {
    y -= 1;
}

void Hero::go_left() {
    x -= 1;
}

void Hero::go_right() {
    x += 1;
}

size_t Hero::get_x() const {
    return x;
}

size_t Hero::get_y() const {
    return y;
}

size_t Hero::get_wgt() const {
    return wgt;
}

size_t Hero::get_arm() const {
    return arm;
}

void Hero::set_wgt(size_t _wgt) {
    wgt = _wgt;
}

void Hero::set_arm(size_t _arm) {
    arm = _arm;
}

void Hero::kick_arm(size_t dammage) {
    if (arm >= dammage) {
        kick(1);
    } else {
        kick(dammage - arm);
    }
}
