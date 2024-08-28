
#include "ArrowShape.hpp"
#include "math.h"

ArrowShape::ArrowShape(sf::Vector2f& vector_)
: m_vector(vector_)
{
    setOrigin(0.f, 0.5f);
    update();
}

void ArrowShape::update() {

    // base of arrow
    m_tri_base[0].position = sf::Vector2f(0.f, 0.5f);
    m_tri_base[1].position = sf::Vector2f(0.75f, 0.75f);
    m_tri_base[2].position = sf::Vector2f(0.75f, 0.25f);
    // head of arrow
    m_tri_head[0].position = sf::Vector2f(0.75f, 1.f);
    m_tri_head[1].position = sf::Vector2f(1.f, 0.5f);
    m_tri_head[2].position = sf::Vector2f(0.75f, 0.f);

    // Color:  red - longer arrow,  blue - shorter arrow.
    const auto magnitude = std::hypotf(m_vector.x, m_vector.y); // find hypotenuse
    const sf::Color color = sf::Color( 0.f,   std::clamp( magnitude, 0.f, 255.f),
                                            std::clamp(255 - magnitude, 0.f, 255.f), 215.f );

    m_tri_base[0].color = color;
    m_tri_base[1].color = color;
    m_tri_base[2].color = color;
    m_tri_head[0].color = color;
    m_tri_head[1].color = color;
    m_tri_head[2].color = color;


    // angle will be the inverse tangent () of the vector components in degrees
    constexpr float TO_DEGREES = 57.2957804;
    setRotation( -1 * TO_DEGREES * std::atan( m_vector.y / m_vector.x ));

    setScale( { 15 + m_vector.x * 2, std::clamp(fabsf(m_vector.y) / 10, 0.f, 20.f) } );  // just visuals
}

 // MANDATORY by SFML
 void ArrowShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // draw the vertex array
    target.draw(m_tri_base, states);
    target.draw(m_tri_head, states);
}
