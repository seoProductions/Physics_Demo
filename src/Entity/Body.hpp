
#ifndef PHYSICS_DEMO_BODY_HPP
#define PHYSICS_DEMO_BODY_HPP

#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////
////
////  Interface - Base for KinematicBody, RigidBody
////
//////////////////////////////////////////////////////
class Body {
public:

    // invoked by WorldSpace's update() function. located at WorldSpace::InitBehavior(...);
    virtual void update() = 0;
};

#endif //PHYSICS_DEMO_BODY_HPP
