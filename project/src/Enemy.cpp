#include<iostream>
#include <cstddef>

#include "Enemy.h"
Enemy::Enemy(int _hp, size_t _basic_dmg,
            size_t _weapon):
                hp(_hp),
                basic_dmg(_basic_dmg),
                weapon(_weapon) {}

void Enemy::kick(size_t dammage) {
    hp -= dammage;
}

int Enemy::get_hp() const {
    return hp;
}

size_t Enemy:: get_dmg() const {
    return basic_dmg + weapon;
}
