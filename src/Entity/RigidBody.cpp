#include "RigidBody.h"

RigidBody::RigidBody(float x, float y, float mass) {
    m_position.x = x;
    m_position.y = y;
    m_mass       = mass;
}

RigidBody::RigidBody(const sf::Vector2f& pos, float mass)
{
    RigidBody(pos.x, pos.y, mass);
}

void RigidBody::update() {
    // update vectors
    m_position += m_velocity * Time::getDeltaTime();
    m_velocity += m_acceleration * Time::getDeltaTime();
    m_momentum =  m_velocity * m_mass;

    m_acceleration -= m_earth_gravity * Time::getDeltaTime();

    // TODO implement drag

    // update attached object
    m_attached_obj->setPosition(m_position.x,
                                -m_position.y);     // transformable object will have flipped y-axis (negative down)
}

void RigidBody::attachObject(std::shared_ptr<sf::Transformable> obj)
{
    m_attached_obj = obj;
}


sf::Vector2f &RigidBody::getPosition() {
    return m_position;
}

sf::Vector2f &RigidBody::getVelocity() {
    return m_velocity;
}

sf::Vector2f &RigidBody::getAcceleration() {
    return m_acceleration;
}

sf::Vector2f &RigidBody::getMomentum() {
    return m_momentum;
}

float &RigidBody::getMass() {
    return m_mass;
}

void RigidBody::setPosition(const sf::Vector2f &position) {
    RigidBody::m_position = position;
}

void RigidBody::setVelocity(const sf::Vector2f &velocity) {
    RigidBody::m_velocity = velocity;
}

void RigidBody::setAcceleration(const sf::Vector2f &acceleration) {
    RigidBody::m_acceleration = acceleration;
}








// from prev attempt
//void RigidBody::applyResistance() {
    //getVelocity().y += 2.f * Time::getDeltaTime();      //gravity

    //drag
    //decrease the magnitude of acceleration in the x direction. Operations will depend on the current sign of Velocity.x
    //sneaky trick found here: http://graphics.stanford.edu/~seander/bithacks.html#CopyIntegerSign
    //getAcceleration().x -= ((getAcceleration().x > 0) - (getAcceleration().x < 0));
//}