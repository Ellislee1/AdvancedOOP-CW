/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
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
#include <vector>
#include <iostream>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
private:
    int width;
    int height;
    std::vector<Cell> grid;
    [[nodiscard]] int get_index(int x, int y) const;
    static std::ostream &write_row(std::ostream &ostream, int width);
    friend std::ostream& operator<<(std::ostream& output_stream, const Grid& grid);
public:
    Grid();
    explicit Grid(int square_size);
    Grid(int width, int height);
    ~Grid() = default;

    // Getters
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;
    [[nodiscard]] int get_total_cells() const;
    [[nodiscard]] int get_alive_cells() const;
    [[nodiscard]] int get_dead_cells() const;
    [[nodiscard]] Cell get(int x, int y) const;

    // Setters
    void set(int x, int y, Cell value);

    // Operator overload
    Cell& operator()(int x, int y);
    const Cell& operator()(int x, int y)const;

    // Other Functions
    void resize(int square_size);
    void resize(int new_width, int new_height);
    [[nodiscard]] Grid crop(int x0, int y0, int x1, int y1) const;
    void merge(const Grid &other, int x0, int y0, bool alive_only = false);
    [[nodiscard]] Grid rotate(int rotation) const;
};