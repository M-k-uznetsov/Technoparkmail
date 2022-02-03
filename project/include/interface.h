#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>

#include "Map.h"
#include "Enemy.h"
#include "Hero.h"
#include "Clothes.h"

#define SHIFTCLOTHES 4

class interface {
 private:
    Map map;
    Hero hero;
    Enemy enemy;
    Clothes clothes;

    void supported_actions() const;
    void throw_equip(size_t equip, size_t arm, size_t wgt);
    void pick_equip(size_t equip, size_t arm, size_t wgt);
    void message() const;
    void actions();

    bool fight(Enemy& enemy);
    bool check_fight();

 public:
    int game();
    explicit interface(Map& _map);
};
