//
// Created by Project Apollo on 10/03/2020.
//

#include "grid.h"
#include <iostream>

int main(int argc, char *argv[]){
    Grid test1 = Grid();
    std::cout << "test1 w&h "<< test1.get_width() << " " << test1.get_height() << std::endl;

    Grid test2 = Grid(16);
    std::cout << "test2 w&h "<< test2.get_width() << " " << test2.get_height() << std::endl;

    Grid test3 = Grid(12, 12);
    std::cout << "test3 w&h "<< test3.get_width() << " " << test3.get_height() << std::endl;
}
