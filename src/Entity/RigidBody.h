
#ifndef PHYSICS_DEMO_RIGIDBODY_H
#define PHYSICS_DEMO_RIGIDBODY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "../Time.h"

class RigidBody {

public:
    RigidBody(float x, float y, float mass);
    explicit
    RigidBody(const sf::Vector2f& pos, float mass = 1.f);

    void update();

    //getters setters
    sf::Vector2f &getPosition();
    sf::Vector2f &getVelocity();
    sf::Vector2f &getAcceleration();
    sf::Vector2f &getMomentum();
    float&        getMass();

    void setPosition    (const sf::Vector2f &position);
    void setVelocity    (const sf::Vector2f &velocity);
    void setAcceleration(const sf::Vector2f &acceleration);

    void attachObject   (std::shared_ptr<sf::Transformable>);

private:
    // used to link/sync entity's [ m_shape ] pos with entity's [ m_RigidBody ] pos
    std::shared_ptr<sf::Transformable> m_attached_obj;  // external position to modify;

    /////////////////
    ////
    ////  Vector's
    ////
    /////////////////

    //default float values are 0, according to c++
    sf::Vector2f m_position;        // x, y
    sf::Vector2f m_velocity;        // window coords per sec
    sf::Vector2f m_acceleration;    // window coords per sec ^ 2

    sf::Vector2f m_momentum;        // grams window coords per second

    static inline const sf::Vector2f m_earth_gravity  = { 0, 9.81 };
    static inline const sf::Vector2f m_moon_gravity   = { 0, 1.62 };

    /////////////////
    ////
    ////  Scalar's
    ////
    /////////////////

    float m_mass;   // grams

};


#endif //PHYSICS_DEMO_RIGIDBODY_H
