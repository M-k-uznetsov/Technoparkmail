#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>

#include "interface.h"
#include "Map.h"
#include "Enemy.h"
#include "Hero.h"
#include "Clothes.h"
int main(int argc, const char** argv) {
    if (argc < 2) {
        return ERROR;
    }
    int j = 0;
    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "--map") {
            j = i;
        }
    }
    std::ifstream file(argv[j+1]);
    if (file.bad()) {
        return ERROR;
    }

    Map map(file);
    interface interface(map);
    interface.game();
}
