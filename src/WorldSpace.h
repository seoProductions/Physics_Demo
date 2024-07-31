#ifndef PHYSICS_DEMO_WORLDSPACE_H
#define PHYSICS_DEMO_WORLDSPACE_H

#include <SFML/Graphics.hpp>
#include "Entity/Entity.h";

/////////////////////////////////////////////////////////////////////////
////
////    WorldSpace is a structure that stores helpful world data
////    Serves as a base for each interactive world
////
/////////////////////////////////////////////////////////////////////////

struct WorldSpace {

    // world info
    bool        m_isActive;
    std::string m_name;
    sf::View    m_worldview;

    // world entities
    std::vector<Entity> m_entity_list;  // dynamically allocated

    WorldSpace(std::string name) :      // constructor
    m_isActive(false),
    m_name(name)
    {
        m_worldview.setCenter(0.f,0.f);
    }

    void update();  // invoked every frame

};

void inline WorldSpace::update() {

    // Update RigidBod
    for (auto& entity : m_entity_list)
    {
        if (entity.m_RigidBody)
            entity.m_RigidBody->update();
    }
}


#endif //PHYSICS_DEMO_WORLDSPACE_H
