
#ifndef PHYSICS_DEMO_RIGIDBODY_HPP
#define PHYSICS_DEMO_RIGIDBODY_HPP

#include "KinematicBody.hpp"

///////////////////////////////////////////////////////////
////
////  RigidBody - Extension of KinematicBody
////            Allows for complex interactions along forces and
////            other external components.
////
///////////////////////////////////////////////////////////
class RigidBody : public  KinematicBody {

public:
    // constructors
    RigidBody(float x, float y, float mass);
    explicit
    RigidBody(const sf::Vector2f& pos, float mass = 1.f);

    void update() override;

    // getters setters
    sf::Vector2f &getMomentum();
    float&        getMass();

private:

    /////////////////
    ////
    ////  Vector's
    ////
    /////////////////
    sf::Vector2f m_momentum;        // grams window coords per second
    // TODO FIGURE OUT UNITS

    /////////////////
    ////
    ////  Scalar's
    ////
    /////////////////

    float m_mass;   // grams

};


#endif //PHYSICS_DEMO_RIGIDBODY_HPP
