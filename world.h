/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 951536
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...

#include "grid.h"

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
private:
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
    Grid cur_world;
    Grid next_world;
    [[nodiscard]] int count_neighbours(int x, int y, bool toroidal) const;
public:
    World();
    explicit World(int square_size);
    World(int width, int height);
    explicit World(const Grid &initial_state);
    ~World() = default;

    // Getters
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;
    [[nodiscard]] int get_total_cells() const;
    [[nodiscard]] int get_alive_cells() const;
    [[nodiscard]] int get_dead_cells() const;
    [[nodiscard]] const Grid& get_state() const;

    // Others
    void resize(int square_size);
    void resize(int width, int height);

    // step functions
    void step(bool toroidal = false);
    void advance(int steps, bool toroidal = false);
};