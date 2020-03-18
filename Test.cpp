//
// Created by Project Apollo on 10/03/2020.
//

#include "grid.h"
#include "zoo.h"
#include <iostream>

int main(int argc, char *argv[]){
    Grid g = Zoo::load_ascii("../test_inputs/GLIDER.gol");

            std::cout << g << std::endl;

    return 0;
}
