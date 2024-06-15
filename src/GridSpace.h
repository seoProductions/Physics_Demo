
#ifndef PHYSICS_DEMO_GRIDSPACE_H
#define PHYSICS_DEMO_GRIDSPACE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "WorldSpace.h"

class GridSpace {
public:

    static void init(WorldSpace*);
    static void updateGrid();

    static
    const std::vector<sf::VertexArray>& getGridLines();

private:

    inline static WorldSpace* m_current_world;

    // lines
    inline static sf::VertexArray m_origin_verticle;
    inline static sf::VertexArray m_origin_horizontal;

    // collection of lines
    inline static std::vector<sf::VertexArray> m_lines;     // used to draw

    ////////////////////////////////////
    ////
    //// Helpful methods (math)
    ////
    ////////////////////////////////////

    // calculate transparency for a given number of lines
    // more lines = more transparent
    //
    // simply performs 255/line_count
    //
    static constexpr u_char calc_aplha(int line_count);

    // round n_ down to nearest digit_'s place i.e. 10's, 100's, 1,000's
    //
    //  example: 1234 -> 1000
    //  example: 543  -> 500
    //  example: 27  -> 20
    //
    static constexpr float  floor_by_digit(int64_t n_);

    // return most divisible power of 10 for n_
    //
    // example: 543  -> 100
    // example: 4555 -> 1000
    // example: 66   -> 10
    //
    static constexpr int    get_base_10_divisible(int64_t n_);
};


#endif //PHYSICS_DEMO_GRIDSPACE_H
