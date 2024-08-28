
#include "KinematicBody.hpp"

KinematicBody::KinematicBody(float x, float y) {
    m_position.x = x;
    m_position.y = y;

    // set up vector visualizers
    // FIXME: DEFAULT every vector visualizer is enabled
    // FIXME: implement optional "show vector"
    m_arrow_velocity     = std::nullopt;
    m_arrow_acceleration = std::nullopt;

    m_arrow_velocity.emplace(ArrowShape(m_velocity));
    m_arrow_acceleration.emplace(ArrowShape(m_acceleration));
}

KinematicBody::KinematicBody(const sf::Vector2f& pos) : KinematicBody(pos.x, pos.y) { }

void KinematicBody::update() {
    // update vectors
    m_position += m_velocity * Time::getDeltaTime();
    m_velocity += m_acceleration * Time::getDeltaTime();

    m_acceleration -= m_earth_gravity * Time::getDeltaTime();

    // update attached object
    m_attached_obj->setPosition(m_position.x,
                                -m_position.y);     // transformable object will have flipped y-axis (negative down)

    // update vector visualizers
    m_arrow_velocity->update();
    m_arrow_velocity->setPosition(m_position.x,
                                  -m_position.y);
    m_arrow_acceleration->setPosition(m_position.x,
                                      -m_position.y);
    m_arrow_acceleration->update();
}

// TODO Bug?
void KinematicBody::attachObject(const std::shared_ptr<sf::Transformable>& obj)
{
    m_attached_obj = obj;
}


sf::Vector2f &KinematicBody::getPosition() {
    return m_position;
}

sf::Vector2f &KinematicBody::getVelocity() {
    return m_velocity;
}

sf::Vector2f &KinematicBody::getAcceleration() {
    return m_acceleration;
}

void KinematicBody::setPosition(const sf::Vector2f &position) {
    m_position = position;
}

void KinematicBody::setVelocity(const sf::Vector2f &velocity) {
    m_velocity = velocity;
}

void KinematicBody::setAcceleration(const sf::Vector2f &acceleration) {
    m_acceleration = acceleration;
}
