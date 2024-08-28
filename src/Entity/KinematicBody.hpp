
#ifndef PHYSICS_DEMO_KINEMATICBODY_HPP
#define PHYSICS_DEMO_KINEMATICBODY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>
#include "Body.hpp"
#include "../ArrowShape.hpp"
#include "../Time.hpp"


///////////////////////////////////////////////////////////
////
////  Kinematics - Allows for simple & smooth 2D movement.
////
///////////////////////////////////////////////////////////
class KinematicBody : public Body {

public:
    // constructors
    KinematicBody(float x, float y);
    explicit
    KinematicBody(const sf::Vector2f& pos);

    void update() override;

    // Vector Visualizer's
    std::optional<ArrowShape>   m_arrow_velocity;
    std::optional<ArrowShape>   m_arrow_acceleration;

    // getters setters
    sf::Vector2f &getPosition();
    sf::Vector2f &getVelocity();
    sf::Vector2f &getAcceleration();

    void setPosition    (const sf::Vector2f &position);
    void setVelocity    (const sf::Vector2f &velocity);
    void setAcceleration(const sf::Vector2f &acceleration);

    void attachObject   (const std::shared_ptr<sf::Transformable>&);


protected:
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

    static inline const sf::Vector2f m_earth_gravity  = { 0, 9.81 };
    static inline const sf::Vector2f m_moon_gravity   = { 0, 1.62 };

};


#endif //PHYSICS_DEMO_KINEMATICBODY_HPP
