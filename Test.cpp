//
// Created by Project Apollo on 10/03/2020.
//

#include "grid.h"
#include "zoo.h"
#include "world.h"
#include <iostream>

int main(int argc, char *argv[]){
    World w(8);
    std::cout << w.get_state() << std::endl;;

    return 0;
}
