#include "RigidBody.hpp"

RigidBody::RigidBody(float x, float y, const float mass)
:   KinematicBody(x, y) {
    m_mass      = mass;
}

RigidBody::RigidBody(const sf::Vector2f& pos, const float mass)
:   KinematicBody(pos) {
    m_mass      = mass;
}

void RigidBody::update() {
    // update vectors
    KinematicBody::update();
    m_momentum =  m_velocity * m_mass;

    // TODO implement drag
}

sf::Vector2f &RigidBody::getMomentum() {
    return m_momentum;
}

float &RigidBody::getMass() {
    return m_mass;
}








// from prev attempt
//void RigidBody::applyResistance() {
    //getVelocity().y += 2.f * Time::getDeltaTime();      //gravity

    //drag
    //decrease the magnitude of acceleration in the x direction. Operations will depend on the current sign of Velocity.x
    //sneaky trick found here: http://graphics.stanford.edu/~seander/bithacks.html#CopyIntegerSign
    //getAcceleration().x -= ((getAcceleration().x > 0) - (getAcceleration().x < 0));
//}