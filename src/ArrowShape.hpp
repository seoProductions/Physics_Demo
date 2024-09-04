
#ifndef PHYSICS_DEMO_ARROWSHAPE_HPP
#define PHYSICS_DEMO_ARROWSHAPE_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class ArrowShape : public sf::Drawable, public sf::Transformable {
public:
    explicit ArrowShape(sf::Vector2f&);

    void update();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    sf::VertexArray m__base      { sf::Quads, 4 };
    sf::VertexArray m__head_1    { sf::Quads, 4 };
    sf::VertexArray m__head_2    { sf::Quads, 4 };
    sf::Vector2f&   m_vector;       // reference to the vector it visualizes
};


#endif //PHYSICS_DEMO_ARROWSHAPE_HPP
