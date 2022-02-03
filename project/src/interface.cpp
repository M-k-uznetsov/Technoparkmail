#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

#include "interface.h"
#include "Map.h"
#include "Enemy.h"
#include "Hero.h"
#include "Clothes.h"

interface::interface(Map& _map): map(_map), hero(), clothes()
{}

void interface:: supported_actions() const {
    std::cout << "Supported actions:\n";
    bool is_dop_spase = true;
    if (hero.get_x() > 0) {
        std::cout << " * move left\n";
        is_dop_spase = false;
    }
    if (hero.get_x() != (map.get_max_x() - 1)) {
        std::cout << " * move right\n";
        is_dop_spase = false;
    }
    if (hero.get_y() > 0) {
        std::cout << " * move down\n";
        is_dop_spase = false;
    }
    if (hero.get_y() != (map.get_max_y() - 1)) {
        std::cout << " * move up\n";
        is_dop_spase = false;
    }

    if (map[hero.get_x()][hero.get_y()] == TSHIRT &&
        clothes[TSHIRT - SHIFTCLOTHES] == false) {
            std::cout << " * pick T-Shirt\n";
    }
    if (map[hero.get_x()][hero.get_y()] == ARMOR &&
        clothes[ARMOR - SHIFTCLOTHES] == false) {
            std::cout << " * pick armor\n";
    }
    if (map[hero.get_x()][hero.get_y()] == HELMET &&
        clothes[HELMET - SHIFTCLOTHES] == false) {
            std::cout << " * pick helmet\n";
    }
    if (map[hero.get_x()][hero.get_y()] == PANTS &&
        clothes[PANTS - SHIFTCLOTHES] == false) {
            std::cout << " * pick pants\n";
    }
    if (map[hero.get_x()][hero.get_y()] == SHIELD &&
        clothes[SHIELD - SHIFTCLOTHES] == false) {
            std::cout << " * pick shield\n";
    }

    if (map[hero.get_x()][hero.get_y()] != NOTHING) {
        if (clothes[TSHIRT - SHIFTCLOTHES] == true) {
            std::cout << " * throw T-Shirt\n";
        }
        if (clothes[ARMOR - SHIFTCLOTHES] == true) {
            std::cout << " * throw armor\n";
        }
        if (clothes[HELMET - SHIFTCLOTHES] == true) {
            std::cout << " * throw helmet\n";
        }
        if (clothes[PANTS - SHIFTCLOTHES] == true) {
            std::cout << " * throw pants\n";
        }
        if (clothes[SHIELD - SHIFTCLOTHES] == true) {
            std::cout << " * throw shield\n";
        }
    }

    if (is_dop_spase == true) {
        std::cout << '\n';
    }
    std::cout << hero.get_x() << " x "
        << hero.get_y() << ", hp: "
        << hero.get_hp() << ", armor: "
        << hero.get_arm() << " > ";
}

void interface::throw_equip(
                size_t equip, size_t arm, size_t wgt) {
    clothes[equip - 4] = false;
    hero.set_arm(hero.get_arm() - arm);
    hero.set_wgt(hero.get_wgt() - wgt);
}

void interface::pick_equip(
                size_t equip, size_t arm, size_t wgt) {
    clothes[equip - 4] = true;
    hero.set_arm(hero.get_arm() + arm);
    hero.set_wgt(hero.get_wgt() + wgt);
    std::cout << "\nclothes worn\n";
}

void interface:: message() const {
    if (map[hero.get_x()][hero.get_y()] == ARMOR) {
        std::cout << "\narmor found\n";
    }
    if (map[hero.get_x()][hero.get_y()] == HELMET) {
        std::cout << "\nhelmet found\n";
    }
    if (map[hero.get_x()][hero.get_y()] == SHIELD) {
        std::cout << "\nshield found\n";
    }
    if (map[hero.get_x()][hero.get_y()] == PANTS) {
        std::cout << "\npants found\n";
    }
    if (map[hero.get_x()][hero.get_y()] == TSHIRT) {
        std::cout << "\nT-Shirt found\n";
    }
}

void interface:: actions() {
    std::string user_input, user, input;
    std::cin >> user >> input;
    user_input = user + ' ' + input;
    if (user_input == "move left" && hero.get_x() > 0) {
        map[hero.get_x()][hero.get_y()] = NOTHING;
        hero.go_left();
        if (map[hero.get_x()][hero.get_y()] == NOTHING) {
            std::cout << "\nmoved\n";
            if (std::cin.eof()) {
                supported_actions();
            }
        } else {
            message();
        }
    }
    if (user_input == "move right" &&
       (hero.get_x() != (map.get_max_x() - 1))) {
            map[hero.get_x()][hero.get_y()] = NOTHING;
            hero.go_right();
            if (map[hero.get_x()][hero.get_y()] == NOTHING) {
                std::cout << "\nmoved\n";
                if (std::cin.eof()) {
                    supported_actions();
                }
            } else {
                message();
            }
    }
    if (user_input == "move down" && hero.get_y() > 0) {
        map[hero.get_x()][hero.get_y()] = NOTHING;
        hero.go_down();
        if (map[hero.get_x()][hero.get_y()] == NOTHING) {
            std::cout << "\nmoved\n";
            if (std::cin.eof()) {
                supported_actions();
            }
        } else {
            message();
        }
    }
    if (user_input == "move up" &&
        hero.get_y() != (map.get_max_y() - 1)) {
            map[hero.get_x()][hero.get_y()] = NOTHING;
            hero.go_up();
            if (map[hero.get_x()][hero.get_y()] == NOTHING) {
                std::cout << "\nmoved\n";
                if (std::cin.eof()) {
                    supported_actions();
                }
            } else {
                message();
        }
    }

    if (user_input == "pick armor" && hero.get_wgt() + ARMORWGT <= 20 &&
    clothes[ARMOR - 4] == 0 && map[hero.get_x()][hero.get_y()] == ARMOR) {
        map[hero.get_x()][hero.get_y()] = NOTHING;
        pick_equip(ARMOR, ARMORARM, ARMORWGT);
    }
    if (user_input == "throw armor" && clothes[ARMOR - 4] != 0) {
        throw_equip(ARMOR, ARMORARM, ARMORWGT);
        std::cout << "\nthe armor is thrown out\n";
    }

    if (user_input == "pick helmet" && hero.get_wgt() + HELMETWGT <= 20 &&
        clothes[HELMET - 4] == 0 && map[hero.get_x()][hero.get_y()] == HELMET) {
        map[hero.get_x()][hero.get_y()] = NOTHING;
        pick_equip(HELMET, HELMETARM, HELMETWGT);
    }
    if (user_input == "throw helmet" && clothes[HELMET - 4] != 0) {
        throw_equip(HELMET, HELMETARM, HELMETWGT);
        std::cout << "\nthe helmet is thrown out\n";
    }

    if (user_input == "pick shield" && hero.get_wgt() + SHIELDWGT <= 20 &&
        clothes[SHIELD - 4] == 0 && map[hero.get_x()][hero.get_y()] == SHIELD) {
        map[hero.get_x()][hero.get_y()] = NOTHING;
        pick_equip(SHIELD, SHIELDARM, SHIELDWGT);
    }
    if (user_input == "throw shield" && clothes[SHIELD - 4] != 0) {
        throw_equip(SHIELD, SHIELDARM, SHIELDWGT);
        std::cout << "\nthe shield is thrown out\n";
    }

    if (user_input == "pick pants" && hero.get_wgt() + PANTSWGT <= 20 &&
        clothes[PANTS - 4] == 0 && map[hero.get_x()][hero.get_y()] == PANTS) {
        map[hero.get_x()][hero.get_y()] = NOTHING;
        pick_equip(PANTS, PANTSARM, PANTSWGT);
    }
    if (user_input == "throw pants" && clothes[PANTS - 4] != 0) {
        throw_equip(PANTS, PANTSARM, PANTSWGT);
        std::cout << "\nthe pants is thrown out\n";
    }

    if (user_input == "pick T-Shirt" && hero.get_wgt() + TSHIRTWGT <= 20 &&
        clothes[TSHIRT - 4] == 0 && map[hero.get_x()][hero.get_y()] == TSHIRT) {
        map[hero.get_x()][hero.get_y()] = NOTHING;
        pick_equip(TSHIRT, TSHIRTARM, TSHIRTWGT);
    }
    if (user_input == "throw T-Shirt" && clothes[TSHIRT - 4] != 0) {
        throw_equip(TSHIRT, TSHIRTARM, TSHIRTWGT);
        std::cout << "\nthe T-Shirt is thrown out\n";
    }
}

bool interface::fight(Enemy& enemy) {
    size_t from_hero = hero.get_dmg();
    size_t from_enemy = enemy.get_dmg();
    while (std::cin && hero.get_hp() > 0 && enemy.get_hp() > 0) {
        std::cout << "\nSupported actions:\n * kick enemy\n";
        std::cout<< hero.get_x() << " x "
                 << hero.get_y() << ", hp: "
                 << hero.get_hp() << ", armor: "
                 << hero.get_arm() << " > ";
        std::string user_input, user, input;
        std::cin >> user >> input;
        user_input = user + ' ' + input;
        if (user_input == "kick enemy" && hero.get_hp() > 0) {
            enemy.kick(from_hero);
            if (enemy.get_hp() > 0) {
                if (hero.get_hp() + static_cast<int>(hero.get_arm()) > static_cast<int>(from_enemy) &&
                    hero.get_hp() > 1 ) {
                        std::cout << "\nenemy kicked. Enemy hp: " << enemy.get_hp();
                }
            } else {
                std::cout << "\nenemy killed\n";
                map[hero.get_x()][hero.get_y()] = 0;
                return true;
            }
        }
        hero.kick_arm(from_enemy);
        if (hero.get_hp() <= 0) {
            std::cout << "\nplayer died" << std::endl;
            return false;
        }
    }
    return true;
}

bool interface:: check_fight() {
    size_t x = hero.get_x();
    size_t y = hero.get_y();
    if (map[x][y] == 1) {
        std::cout << "\nwolf found, 6 hp";
        Enemy enemy(6, 10, 1);
        return fight(enemy);
    } else if (map[x][y] == 2) {
        std::cout << "\ndog found, 3 hp";
        Enemy enemy(3, 5, 1);
        return fight(enemy);
    } else if (map[x][y] == 3) {
        std::cout << "\nrat found, 2 hp";
        Enemy enemy(2, 3, 1);
        return fight(enemy);
    }
    return true;
}

int interface::game() {
    while (hero.get_hp() > 0&& !std::cin.eof()) {
        if (check_fight() == true) {
            supported_actions();
            actions();
        } else {
            return 0;
        }
    }
    return 0;
}
