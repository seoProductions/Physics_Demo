#ifndef PHYSICS_DEMO_WORLDSPACE_H
#define PHYSICS_DEMO_WORLDSPACE_H

#include <SFML/Graphics.hpp>
#include "GridSpace.h"

struct WorldSpace {
    bool        m_isActive;
    std::string m_name;
    sf::View    m_worldview;
    //entities
    sf::RectangleShape  m_shape;

    WorldSpace(std::string name)
    :
    m_isActive(false),
    m_name(name)
    {
        m_worldview.setCenter(0.f,0.f);
    }
};


#endif //PHYSICS_DEMO_WORLDSPACE_H
