
#include "ArrowShape.hpp"
#include "math.h"

ArrowShape::ArrowShape(sf::Vector2f& vector_)
: m_vector(vector_)
{
    setOrigin(0.f, 0.5f);
    update();
}

void ArrowShape::update() {
    // TODO REDRAW ARROW
    // base of arrow
    m__base[0].position = sf::Vector2f(0.f, 0.25f);
    m__base[1].position = sf::Vector2f(0.f, 0.75f);
    m__base[2].position = sf::Vector2f(0.8f, 0.75f);
    m__base[3].position = sf::Vector2f(0.8f, 0.25f);
    // head of arrow is composed of 2 quadrilaterals
    m__head_1[0].position = sf::Vector2f(0.8f, 0.5f);
    m__head_1[1].position = sf::Vector2f(0.75f, 0.f);
    m__head_1[2].position = sf::Vector2f(0.8f, 0.f);
    m__head_1[3].position = sf::Vector2f(1.f, 0.5f);
    m__head_2[0].position = sf::Vector2f(0.8f, 0.5f);
    m__head_2[1].position = sf::Vector2f(0.75f, 1.f);
    m__head_2[2].position = sf::Vector2f(0.8f, 1.f);
    m__head_2[3].position = sf::Vector2f(1.f, 0.5f);




    // Color:  red - longer arrow,  blue - shorter arrow
    //const auto magnitude  = std::hypotf( m_vector.x, m_vector.y );
    //const sf::Color color = sf::Color( std::clamp( magnitude, 0.f, 255.f), 0.f,
    //                                   std::clamp(255 - magnitude, 0.f, 255.f), 255.f );
    const sf::Color color = sf::Color(150, 220, 250, 255);

    m__base[0].color = sf::Color::Transparent;
    m__base[1].color = sf::Color::Transparent;
    m__base[2].color = color;
    m__base[3].color = color;
    m__head_1[0].color = color;
    m__head_1[1].color = color;
    m__head_1[2].color = color;
    m__head_1[3].color = color;
    m__head_2[0].color = color;
    m__head_2[1].color = color;
    m__head_2[2].color = color;
    m__head_2[3].color = color;

    setScale( { m_vector.x * 2.f, 7.f } );  // just visuals

    // angle will be the inverse tangent () of the vector components in degrees
    constexpr float TO_DEGREES = 57.2957804;
    setRotation( -1 * TO_DEGREES * std::atan( m_vector.y / m_vector.x ));
}

 // MANDATORY by SFML
 void ArrowShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // draw the vertex array
    target.draw(m__base, states);
    target.draw(m__head_1, states);
    target.draw(m__head_2, states);
}
