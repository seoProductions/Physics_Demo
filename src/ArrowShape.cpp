
#include "ArrowShape.hpp"
#include "math.h"

ArrowShape::ArrowShape(sf::Vector2f& vector_)
: m_vector(vector_)
{
    update();
}


void ArrowShape::update() {

    // quad
    m_quad_vertices[0].position = sf::Vector2f(0.f, 0.75f);
    m_quad_vertices[1].position = sf::Vector2f(0.75f, 0.75f);
    m_quad_vertices[2].position = sf::Vector2f(0.75f, 0.25f);
    m_quad_vertices[3].position = sf::Vector2f(0.f, 0.25f);
    // tri
    m_tri_vertices[0].position = sf::Vector2f(0.75f, 1.f);
    m_tri_vertices[1].position = sf::Vector2f(1.f, 0.5f);
    m_tri_vertices[2].position = sf::Vector2f(0.75f, 0.f);

    // COLOR
    const sf::Color c { 200, 232, 133 };    // random color TODO color by magnitude
    m_quad_vertices[0].color = c;
    m_quad_vertices[1].color = c;
    m_quad_vertices[2].color = c;
    m_quad_vertices[3].color = c;
    m_tri_vertices[0].color = c;
    m_tri_vertices[1].color = c;
    m_tri_vertices[2].color = c;


    // angle will be the inverse tangent () of the vector components in degrees
    constexpr float TO_DEGREES = 57.2957804;
    setRotation( -1 * TO_DEGREES * std::atan( m_vector.y / m_vector.y ));

    setOrigin(0.f, 0.5f);
    setScale( { m_vector.x, m_vector.y / 5 });  // just visuals
}

 // MANDATORY by SFML
 void ArrowShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // draw the vertex array
    target.draw(m_quad_vertices, states);
    target.draw(m_tri_vertices, states);
}
