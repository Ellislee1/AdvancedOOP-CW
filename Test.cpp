//
// Created by Project Apollo on 10/03/2020.
//

#include "grid.h"
#include <iostream>

int main(int argc, char *argv[]){
    Grid w(8, 8);

    for (int y = 2; y < 6; y++) {
        for (int x = 2; x < 6; x++) {
            w.set(x, y, Cell::ALIVE);
        }
    }

    Grid h = w.crop(0, 0, 4, 4);

    std::cout << h << std::endl;
    std::cout << w << std::endl;

    return 0;
}
