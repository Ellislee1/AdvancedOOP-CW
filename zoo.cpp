/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 951536
 * @date March, 2020
 */
#include "zoo.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...
#include "grid.h"
#include <fstream>
#include <cmath>

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider(){
    Grid glider(3);
    glider.set(1,0, Cell::ALIVE);
    glider.set(2,1, Cell::ALIVE);
    glider.set(0,2, Cell::ALIVE);
    glider.set(1,2, Cell::ALIVE);
    glider.set(2,2, Cell::ALIVE);

    return glider;
}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino(){
    Grid r_pentomino(3);

    r_pentomino.set(1,0, Cell::ALIVE);
    r_pentomino.set(2,0, Cell::ALIVE);
    r_pentomino.set(0,1, Cell::ALIVE);
    r_pentomino.set(1,1, Cell::ALIVE);
    r_pentomino.set(1,2, Cell::ALIVE);

    return r_pentomino;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 3x3 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship(){
    Grid light_weight_spaceship(5,4);

    light_weight_spaceship.set(1,0, Cell::ALIVE);
    light_weight_spaceship.set(4,0, Cell::ALIVE);
    light_weight_spaceship.set(0,1, Cell::ALIVE);
    light_weight_spaceship.set(0,2, Cell::ALIVE);
    light_weight_spaceship.set(4,2, Cell::ALIVE);
    light_weight_spaceship.set(0,3, Cell::ALIVE);
    light_weight_spaceship.set(1,3, Cell::ALIVE);
    light_weight_spaceship.set(2,3, Cell::ALIVE);
    light_weight_spaceship.set(3,3, Cell::ALIVE);

    return light_weight_spaceship;
}


/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(std::string const& path) {
    // open
    std::ifstream read;
    read.open(path);

    // Check open
    if(!read){
        throw std::runtime_error("Zoo::load_ascii(): Could not open file, path does not exist:" + path);
    }

    char c = read.get();
    int width = c-'0'; // Get int value
    read.get();
    c = read.get();
    int height = c-'0';

    // check valid size
    if (width < 0 || height < 0){
        throw std::runtime_error("Zoo::load_ascii(): Error, a negative width or height was set, check file.");
    }
    read.get(); // get blank character

    // create file
    Grid from_file(width,height);
    for (int y = 0; y < height; y++){
        for (int x = 0; x <= width; x++){
            c = read.get();
            // Handle exception
            if(x == width){
                if (c != 10){
                    read.close();
                    throw std::runtime_error("Zoo::load_ascii(): Newline character expected and not found ln:" + std::to_string(y));
                } else {
                    // Dont need to run rest of this iteration
                    continue;
                }
            }

            // handle exception
            if(c == 35){
                from_file.set(x,y, Cell::ALIVE);
            } else if (c != 32) {
                read.close();
                throw std::runtime_error("Zoo::load_ascii(): Character found is not an expected character: " + std::to_string(c));
            }
        }
    }

    read.close();

    return from_file;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(const std::string& path, const Grid& grid){
    // open file
    std::ofstream write(path, std::ofstream::out);
    // fail if not opened
    if(!write){
        throw std::runtime_error("Zoo::save_ascii(): Could not open file, path does not exist:" + path);
    }

    // get width and height
    int width = grid.get_width();
    int height = grid.get_height();

    // write that
    write << width << " " << height << std::endl;

    // Loop through grid writing
    for (int y = 0; y< height; y++){
        for (int x = 0; x<width; x++){
            if(grid.get(x,y) == Cell::ALIVE){
                write << "#";
            } else {write << " ";}

        }
        write << std::endl;
    }

    // Close
    write.close();
}


/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(const std::string& path){
    // open file
    std::ifstream in;
    in.open(path, std::ios::binary | std::ios::in);

    // check file was opened
    if(!in){
        in.close();
        throw std::runtime_error("Zoo::load_binary(): Could not open file, path does not exist:" + path);
    }

    // work out size of file
    const int start = in.tellg();
    in.seekg(0,std::ios::end);
    const int end = in.tellg();
    const int size = end - start;
    in.seekg(0,std::ios::beg);

    // if the size of the file is less than the required 8 bytes file is too short.
    if(size < 8){
        in.close();
        throw std::runtime_error("Zoo::load_binary(): Unexpected end of file");
    }

    // width and height and written grid
    int width;
    int height;

    // Read the width and heights
    in.read((char *) &width, 4);
    in.read((char *) &height, 4);

    // bytes remaining
    int remainder = std::ceil((width * height)/8);
    // Check enough bytes exist in the file
    if (size - 8 < remainder){
        in.close();
        throw std::runtime_error("Zoo::load_binary(): Unexpected end of file");
    }
    int bit_grid;
    // Read bytes into the bit grid
    in.read((char *)&bit_grid, (size - 8));
    // Close the file
    in.close();
    // Make the grid
    Grid grid(width, height);

    // loop through checking each bit adding a alive if cell is alive
    for (int y = 0; y < height; y++){
        int offset = width * y;
        for (int x=0; x<width; x++) {
            int curbit = (bit_grid >> (x + offset)) & 1;
            if (curbit == 1) {
                grid.set(x, y, Cell::ALIVE);
            }
        }
    }

    return grid;
}


/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
*/
void Zoo::save_binary(const std::string& path, const Grid& grid) {
    // Get width and height
    int width = grid.get_width();
    int height = grid.get_height();

    // The total required bits
    int required = width * height;

    // Find number of bytes (add padding first if needed)
    if (required%8 != 0){
        required += (8-(required%8));
    }
    required = required/8;

    // of stream
    std::ofstream out;
    out.open(path, std::ios::binary | std::ios::out);

    // Check file was opened
    if(!out){
        out.close();
        throw std::runtime_error("Zoo::save_binary(): Could not open file, path does not exist:" + path);
    }

    // Write the 4byte size
    out.write((char*)&width, 4);
    out.write((char*)&height, 4);

    // set the bit grid
    int bit_grid = 0;
    // To count written bits
    int counter = 0;
    // To count written bytes
    int tracker = 0;

    for (int y = 0; y < height; y++){
        int offset = width * y;
        for (int x=0; x<width; x++) {
            if (grid.get(x,y) == Cell::ALIVE){
                // Flip the bit in the integer to a 1 if cell is alive
                bit_grid |= 1 << (x+offset);
            }
            ++counter; // increase counter by 1
            // If we reach the size of the integer
            if (counter > 32){
                // write the integer as bits
                out.write((char*)&bit_grid, sizeof(int));
                // reset vars
                counter = 0;
                bit_grid = 0;
                // increase tracker by 4(bytes)
                tracker +=4;
            }
        }
    }

    // Write remaining bytes
    if(tracker != required/8) {
        out.write((char *) &bit_grid, required - tracker);
    }
    // Close the stream.
    out.close();

}
