//
// Created by Project Apollo on 10/03/2020.
//

#include "grid.h"
#include <iostream>

int main(int argc, char *argv[]){
    Grid test1 = Grid();
    std::cout << "test1 w&h "<< test1.get_width() << " " << test1.get_height() << std::endl;
    std::cout << "test1 size "<< test1.get_total_cells() << std::endl;

    Grid test2 = Grid(16);
    std::cout << "test2 w&h "<< test2.get_width() << " " << test2.get_height() << std::endl;
    std::cout << "test2 size "<< test2.get_total_cells() << std::endl;

    Grid test3 = Grid(12, 12);
    std::cout << "test3 w&h "<< test3.get_width() << " " << test3.get_height() << std::endl;
    std::cout << "test3 size "<< test3.get_total_cells() << std::endl;
    std::cout << "test3 alive "<< test3.get_alive_cells() << std::endl;
    std::cout << "test3 dead "<< test3.get_dead_cells() << std::endl;
}
