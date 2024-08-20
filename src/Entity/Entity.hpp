#ifndef PHYSICS_DEMO_ENTITY_HPP
#define PHYSICS_DEMO_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

// including Physics Attributes
#include "Body.hpp"
#include "KinematicBody.hpp"
#include "RigidBody.hpp"

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

    std::shared_ptr<Body> m_body = nullptr;

    //TODO
    // rotational body
    // collidable
};


#endif //PHYSICS_DEMO_ENTITY_HPP
