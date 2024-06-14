
#include "GridSpace.h"

void GridSpace::init(WorldSpace* world_)
{
    m_current_world = world_;

    // initializing origin lines
    m_origin_verticle.  setPrimitiveType(sf::PrimitiveType::Lines);
    m_origin_horizontal.setPrimitiveType(sf::PrimitiveType::Lines);

    m_origin_verticle.  resize(2);
    m_origin_horizontal.resize(2);

    m_origin_verticle[0].color = sf::Color::Red;
    m_origin_verticle[1].color = sf::Color::Red;
    m_origin_horizontal[0].color = sf::Color::Red;
    m_origin_horizontal[1].color = sf::Color::Red;

}

void GridSpace::updateGrid() {

    // setup origin lines
    m_lines =   { m_origin_horizontal,
                  m_origin_verticle };  // default to origin lines

    const sf::View& view = m_current_world->m_worldview;

    // positioning
    m_origin_horizontal[0].position = { view.getCenter().x - (view.getSize().x / 2.f), view.getCenter().y };
    m_origin_horizontal[1].position = { view.getCenter().x + (view.getSize().x / 2.f), view.getCenter().y };

    m_origin_verticle[0].position = { view.getCenter().x, view.getCenter().y - (view.getSize().y / 2.f) };
    m_origin_verticle[1].position = { view.getCenter().x, view.getCenter().y + (view.getSize().y / 2.f) };

}

const std::vector<sf::VertexArray> &GridSpace::getGridLines() {
    return m_lines;
}


