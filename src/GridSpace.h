
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

    //lines
    inline static sf::VertexArray m_origin_verticle;
    inline static sf::VertexArray m_origin_horizontal;

    inline static std::vector<sf::VertexArray> m_lines;

};


#endif //PHYSICS_DEMO_GRIDSPACE_H
