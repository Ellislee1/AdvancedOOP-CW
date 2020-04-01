/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 951536
 * @date March, 2020
 */

// Include the minimal number of headers needed to support your implementation.
// #include ...
#include <iostream>
#include <vector>
#include <algorithm>
#include "grid.h"

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */
Grid::Grid() : Grid(0,0){} // Default constructor, call grid with width and height set to 0

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(const int square_size): Grid(square_size,square_size){} // Call gird with and height the same

/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
Grid::Grid(const int width, const int height) {
    this->width = width;
    this->height = height;
    const int size = width*height;
    this->grid = std::vector<Cell>(size, Cell::DEAD);
}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */
int Grid::get_width() const{
    const int var_width = width; // Get the width
    return var_width;
}


/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */
int Grid::get_height() const{
    const int var_height = height; // get the height
    return var_height;
}

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
 int Grid::get_total_cells() const{
     // The size is how many cells are in the vector.
     const int size = grid.size(); // Get the size
     return size;
 }


/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
 int Grid::get_alive_cells() const{
     const int no_alive = std::count(grid.begin(),grid.end(),Cell::ALIVE);
     return no_alive;
 }



/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
int Grid::get_dead_cells() const{
    const int no_dead = std::count(grid.begin(),grid.end(),Cell::DEAD);
    return no_dead;
}


/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void Grid::resize(const int square_size){
    resize(square_size,square_size);
}

/**
 * Grid::resize(new_width, new_height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void Grid::resize(const int new_width,const int new_height){
    // Dont need to resize if it is the same size
    if(new_width == width && new_height == height){return;}
    // No negative sizes
    if(new_width < 0 || new_height < 0){throw std::runtime_error("Grid::resize() : Negative sizes are not valid dimensions");}

    // Create a new grid
    Grid new_grid(new_width, new_height);

    // Set the maximum x and y to the smallest of the widths and heights respectively
    const int x_max = (width > new_width) ? new_width : width;
    const int y_max = (height > new_height) ? new_height : height;


    for(int y = 0; y < y_max; y++){
        for(int x = 0; x < x_max; x++){
            if(get(x,y) == Cell::ALIVE){
                new_grid.set(x,y,Cell::ALIVE);
            }
        }
    }

    // Replace the grid, width and heights.
    grid = new_grid.grid;
    width = new_grid.width;
    height = new_grid.height;
}


/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */
int Grid::get_index(const int x, const int y) const{
    const int offset = y * width;
    return offset + x;
}


/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell Grid::get(const int x, const int y) const{
    // Check that the values aren't out of bounds
    if (x > (width)-1 || y > (height)-1){
        throw std::runtime_error("Grid::get() : Not a valid grid coordinate");
    }
    // Check that the values aren't negative
    if (x < 0 || y < 0){
        throw std::runtime_error("Grid::get() : Not a valid grid coordinate");
    }

    const int index = get_index(x, y);

    // If the value is alive return alive otherwise dead.
    return (grid.at(index) == Cell::ALIVE) ? Cell::ALIVE : Cell::DEAD;

}


/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
void Grid::set(const int x, const int y, const Cell value) {
    // Check that the values aren't out of bounds
    if (x > width || y > height){
        throw std::runtime_error("Grid::set() : Not a valid grid coordinate, too high");
    }
    // Check that the values aren't out of bounds
    if (x < 0 || y < 0){
        throw std::runtime_error("Grid::set() : Not a valid grid coordinate, too low");
    }
    // Check that the values aren't out of bounds
    const int index = get_index(x, y);
    grid[index] = value;
}


/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell& Grid::operator()(const int x, const int y) {
    // Check that the values aren't out of bounds
    if (x > width || y > height){
        throw std::runtime_error("Grid::operator() : Not a valid grid coordinate");
    }
    // Check that the values aren't out of bounds
    if(x < 0 || y< 0){
        throw std::runtime_error("Grid::operator() : Not a valid grid coordinate");
    }

    // Get index and return reference
    const int index = get_index(x, y);
    Cell & cell = grid.at(index);
    return cell;
}


/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
const Cell & Grid::operator()(const int x, const int y) const {
    // Check that the values aren't out of bounds
    if (x > width || y > height){
        throw std::runtime_error("Grid::operator() : Not a valid grid coordinate");
    }
    // Check that the values aren't out of bounds

    if(x < 0 || y< 0){
        throw std::runtime_error("Grid::operator() : Not a valid grid coordinate");
    }

    // Get index and return reference
    const int index = get_index(x, y);
    const Cell & cell = grid.at(index);
    return cell;
}


/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */
Grid Grid::crop(const int x0, const int y0, const int x1, const int y1) const{
    // Handle invalid sizes
    if ((x0 || x1 )> width || (y0 || y1) > height){
        throw std::runtime_error("Grid::crop() : Not a valid grid coordinate");
    }
    if (x0 < 0 || x1 < 0 || y1 < 0 || y0 < 0){
        throw std::runtime_error("Grid::crop() : Not a valid grid coordinate");
    }

    // Handle reversed inputs
    if(x1 < x0 || y1 < y0){
        throw std::runtime_error("Grid::crop() : Invalid x/y bounds");
    }

    // Get the new width and height of the cropped grid
    const int new_width = x1-x0;
    const int new_height = y1-y0;

    // Create cropped grid
    Grid crop_grid(new_width,new_height);

    // Set the alive vars in the cropped grid
    for(int y = y0; y < y1; y++){
        for(int x = x0; x < x1; x++){
            if(get(x,y) == Cell::ALIVE){
                crop_grid.set(x-x0,y-y0,Cell::ALIVE);
            }
        }
    }

    // Return grid
    return crop_grid;
}


/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */
void Grid::merge(const Grid & other, const int x0, const int y0, const bool alive_only){
    // kept this-> in to make identifying them easier.

    //Get sizes
    const int other_size = other.get_total_cells();
    const int this_size = get_total_cells();

    if(other_size > this_size){
        throw std::runtime_error("Grid::Merge() : The grid is out of bounds");
    }

    if (((x0 + (other.get_width())) > this->width) || ((y0 + (other.get_height())) > this->height)){
        throw std::runtime_error("Grid::Merge() : The grid is out of bounds");
    }

    if(x0 < 0 || y0 < 0){
        throw std::runtime_error("Grid::Merge() : Invalid position");
    }

    for (int y = 0; y < other.get_height(); y++){
        for (int x = 0; x < other.get_width(); x++){
            const Cell state = other.get(x,y);

            if(alive_only){
                if(state == Cell::ALIVE){ // Check to see if the cell is alive
                    this->set(x+x0,y+y0,state);
                }
            } else {
                // Set the value to match no matter what
                this->set(x+x0,y+y0,state);
            }

        }
    }
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
Grid Grid::rotate(int rotation)const{
    int rotations = (rotation%4); // Work out if the grid has been rotated at all
    Grid rotated(this->get_width(), this->get_height()); // set the grid to the current width and height
    rotated.grid = this->grid; // make the current and new grids equal

    if (rotations == 0){
        return rotated; // return the grid
    }

    if(rotation < 0){
        rotations += 4; // Magic maths as %(mod) returns negative numbers and 1 -90 turn == 3 90 turns -1 == 3, -2 == 2 & -3 == 1
    }

    // Loop through the number of rotations
    for (int i = 0; i<rotations; i++){
        Grid temp(rotated.get_height(), rotated.get_width()); // Create temp grid

        // Loop through this grid (Fancy Transpose and reverse rows)
        for (int y = 0; y < temp.get_height(); y++){
            for (int x = 0; x < temp.get_width(); x++){
                if (rotated.get(y,x) == Cell::ALIVE){ // Check if origin cell is alive
                    temp.set((temp.get_width()-1)-x,y, Cell::ALIVE); // transpose and reverse.
                }
            }
        }

        rotated.resize(temp.get_width(), temp.get_height()); // Resize the rotated array to match the temp
        rotated = temp; // copy the temp to the rotated
    }
    
    return rotated;
}


/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */
std::ostream& operator<<(std::ostream& output_stream,const Grid &grid){
    // Write row
    Grid::write_row(output_stream, grid.get_width());

    // Write bulk of grid
    for (int y = 0; y < grid.get_height(); y++){
        output_stream << '|';
        for(int x = 0; x < grid.get_width(); x++){

            if (grid.get(x,y) == Cell::ALIVE){
                output_stream << '#';
            } else {
                output_stream << ' ';
            }

        }
        output_stream << '|'<< std::endl;
    }

    Grid::write_row(output_stream, grid.get_width());
    return output_stream;
}

/**
 * Write a rot of +'s and -'s
 * @param ostream
 *      An ascii mode output stream such as std::cout.
 * @param length
 *      The number of -'s to write
 * @return
 *      Returns the modified os stream
 */
std::ostream &Grid::write_row(std::ostream &ostream, const int length) {
    ostream << '+';

    for(int i=0; i< length; i++){
        ostream << '-';
    }
    ostream << '+'<< std::endl;

    return ostream;
}
