#ifndef PHYSICS_DEMO_ENTITY_H
#define PHYSICS_DEMO_ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "RigidBody.h"

struct Entity {
    std::string m_name;

    // drawable and transformable - thanks to SFML
    std::shared_ptr<sf::Shape> m_shape = nullptr;     // enable polymorphism

    ////////////////////////////////////////
    ////
    ////  Entity Attributes
    ////  Will default to nullptr if not enabled
    ////
    ////////////////////////////////////////

    std::shared_ptr<Body> m_RigidBody = nullptr;
    // collidable
    // rotatable
};


#endif //PHYSICS_DEMO_ENTITY_H
