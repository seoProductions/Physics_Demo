
#ifndef PHYSICS_DEMO_ARROWSHAPE_HPP
#define PHYSICS_DEMO_ARROWSHAPE_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class ArrowShape : public sf::Drawable, public sf::Transformable {
public:
    explicit ArrowShape(sf::Vector2f&);
    explicit ArrowShape(float, float);

    void update();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    sf::VertexArray m_quad_vertices { sf::Quads, 4};
    sf::VertexArray m_tri_vertices  { sf::Triangles, 3};
    sf::Vector2f&   m_vector;
};


#endif //PHYSICS_DEMO_ARROWSHAPE_HPP
