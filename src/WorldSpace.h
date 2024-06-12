#ifndef PHYSICS_DEMO_WORLDSPACE_H
#define PHYSICS_DEMO_WORLDSPACE_H

#include <SFML/Graphics.hpp>
#include "GridSpace.h"

struct WorldSpace {
    bool        m_isActive;
    std::string m_name;
    sf::View    m_worldview;
    GridSpace   m_gridspace;
    //entities
    sf::RectangleShape  m_shape;

    WorldSpace(std::string name) :
    m_isActive(false),
    m_name(name)        { };
};


#endif //PHYSICS_DEMO_WORLDSPACE_H
