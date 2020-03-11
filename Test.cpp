//
// Created by Project Apollo on 10/03/2020.
//

#include "grid.h"
#include <iostream>

int main(int argc, char *argv[]){
    Grid test3 = Grid(8, 8);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            test3.set(j,i,Cell::ALIVE);
        }
    }
    std::cout << test3.get_alive_cells() << std::endl;
    std::cout << test3.get_dead_cells() << std::endl;
    test3.resize(16);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
        }
    }


    std::cout << test3.get_alive_cells() << std::endl;
    std::cout << test3.get_dead_cells() << std::endl;

    return 0;
}
