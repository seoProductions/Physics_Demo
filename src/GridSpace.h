
#ifndef PHYSICS_DEMO_GRIDSPACE_H
#define PHYSICS_DEMO_GRIDSPACE_H

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <vector>

#include "WorldSpace.h"


/////////////////////////////////////////////////////////////////////////
////
////    WorldSpace is a structure that generates drawable grid lines
////    and corresponding text labels
////
/////////////////////////////////////////////////////////////////////////



class GridSpace {
public:

    // game loop action
    static void init(WorldSpace*, sf::RenderWindow*);
    static void updateGrid();

    // drawable containers
    static
    const std::vector<sf::VertexArray>& getGridLines();
    static
    const std::vector<sf::Text>&        getGridLinesText();

    // more containers - non const
    static std::vector<float>&           getDebugInfo();

    // flag
    static
    bool font_available();

    // clamp a given object's position inside the GridSpace
    static void clampPosToGrid(sf::Transformable*, sf::Vector2f pos);
    static void clampPosToGrid(sf::Transformable*, sf::Vector2i pos);
    static void clampPosToGrid(sf::Transformable*, float x, float y);


private:

    inline static WorldSpace*       m_current_world;
    inline static sf::RenderWindow* m_main_window;

    ////////////////////////////////////
    ////
    //// Grid line variables
    ////
    ////////////////////////////////////


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
    static constexpr int    get_base_10_divisible(int64_t n_);  // a better name is base_10_interval

    // calculate transparency for a given number of lines
    // more lines = more transparent
    //
    // simply performs 255 * inv_sqrt(line_count)
    //
    static constexpr u_char calc_alpha(int line_count);

    // clamp
    //https://stackoverflow.com/questions/427477/fastest-way-to-clamp-a-real-fixed-floating-point-value
    static constexpr float clamp(float d, float min, float max);


    ////////////////////////////////////
    ////
    //// Fonts
    ////
    ////////////////////////////////////

    inline static std::vector<sf::Text> m_lines_text;       // line_text displays all sub-line's positions
    inline static sf::Font              m_font;
    inline static bool                  m_font_available;   // cleared if font fail to load

    ////////////////////////////////////
    ////
    //// Debug info
    //// SUB LINES
    ////
    //// 0 - starting x axis subline position (grows right +)
    //// 1 - verticle line interval value
    //// 2 - verticle line total count
    //// 3 - starting y axis subline position (grows up    +)
    //// 4 - horizontal line interval value
    //// 5 - horizontal line total count
    ////
    //// SUB-SUB LINES
    ////
    //// 6 - 11 are the same as 0 - 5
    //// same order, same debug info
    ////
    //////////////////////////////////////
    inline static std::vector<float>     m_debug_vector;
};


#endif //PHYSICS_DEMO_GRIDSPACE_H
