//
// Created by Project Apollo on 10/03/2020.
//

#include "grid.h"
#include <iostream>

int main(int argc, char *argv[]){
    Grid test3 = Grid(4, 4);
    std::cout << "test3 w&h "<< test3.get_width() << " " << test3.get_height() << std::endl;
    std::cout << "test3 size "<< test3.get_total_cells() << std::endl;
    std::cout << "test3 alive "<< test3.get_alive_cells() << std::endl;
    std::cout << "test3 dead "<< test3.get_dead_cells() << std::endl;
    std::cout << "test3 dead "<< (char)test3.get(0,0) << std::endl;
    test3.set(0,0, Cell::ALIVE);
    test3.set(2,1, Cell::ALIVE);
    std::cout << "test3 0,0 "<< (char)test3.get(0,0) << std::endl;
    std::cout << "test3 2,1 "<< (char)test3.get(2,1) << std::endl;
    std::cout << "test3 size "<< test3.get_total_cells() << std::endl;
    std::cout << "test3 alive "<< test3.get_alive_cells() << std::endl;
    std::cout << "test3 dead "<< test3.get_dead_cells() << std::endl;
    test3.resize(8,8);
    std::cout << "test3 0,0 "<< (char)test3.get(0,0) << std::endl;
    std::cout << "test3 2,1 "<< (char)test3.get(2,1) << std::endl;
    std::cout << "test3 size "<< test3.get_total_cells() << std::endl;
    std::cout << "test3 alive "<< test3.get_alive_cells() << std::endl;
    std::cout << "test3 dead "<< test3.get_dead_cells() << std::endl;
    std::cout << "test3 7,5 "<< (char)test3.get(7,5) << std::endl;
    test3.set(7,5, Cell::ALIVE);
    std::cout << "test3 7,5 "<< (char)test3.get(7,5) << std::endl;

    return 0;
}
