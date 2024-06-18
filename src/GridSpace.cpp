
#include <cmath>
#include <imgui.h>
#include <algorithm>

#include "GridSpace.h"

void GridSpace::init(WorldSpace* world_)
{
    m_current_world = world_;

    // initializing origin lines
    m_origin_verticle.  setPrimitiveType(sf::PrimitiveType::Lines);
    m_origin_horizontal.setPrimitiveType(sf::PrimitiveType::Lines);

    m_origin_verticle.  resize(2);
    m_origin_horizontal.resize(2);

    m_origin_verticle[0].color = sf::Color(126, 161, 191);
    m_origin_verticle[1].color = sf::Color(126, 161, 191);
    m_origin_horizontal[0].color = sf::Color(126, 161, 191);
    m_origin_horizontal[1].color = sf::Color(126, 161, 191);

}

void GridSpace::updateGrid() {

    m_lines.clear();

    const sf::View& view = m_current_world->m_worldview;

    ///////////////////////
    ////
    //// Sub-Lines setup
    ////
    ///////////////////////

    float view_edge_x = floor_by_digit(view.getCenter().x - (view.getSize().x / 2));
    float view_edge_y = floor_by_digit(view.getCenter().y - (view.getSize().y / 2));

    // this value determines verticle line spacing
    int base_10_divisible = get_base_10_divisible(view.getSize().x);

    int verticle_count =  view.getSize().x /  base_10_divisible;
    for (int i = 0; i < verticle_count + 1; i++) {
        // vertical sub-lines positioning
        sf::VertexArray sub_vertical(sf::PrimitiveType::Lines, 2);

        sub_vertical[0].color = sf::Color(150, 150, 150, calc_aplha(verticle_count));
        sub_vertical[1].color = sf::Color(150, 150, 150, calc_aplha(verticle_count));

        sub_vertical[0].position = {view_edge_x, view.getCenter().y - (view.getSize().y / 2.f)};
        sub_vertical[1].position = {view_edge_x, view.getCenter().y + (view.getSize().y / 2.f)};

        // add to be drawn
        m_lines.push_back(sub_vertical);

        // update x pos for next verticle line
        view_edge_x += base_10_divisible;
    }

    // this value determines horizontal line spacing
    base_10_divisible = get_base_10_divisible(view.getSize().y);

    int horizontal_count =  view.getSize().y /  base_10_divisible;
    for (int i = 0; i < horizontal_count + 1; i++) {
        // horizontal sub-lines positioning
        sf::VertexArray sub_horizontal(sf::PrimitiveType::Lines, 2);

        sub_horizontal[0].color = sf::Color(150, 150, 150, calc_aplha(horizontal_count));
        sub_horizontal[1].color = sf::Color(150, 150, 150, calc_aplha(horizontal_count));


        sub_horizontal[0].position = { view.getCenter().x - (view.getSize().x / 2.f), view_edge_y };
        sub_horizontal[1].position = { view.getCenter().x + (view.getSize().x / 2.f), view_edge_y };

        // add to be drawn
        m_lines.push_back(sub_horizontal);

        // update x pos for next verticle line
        view_edge_y += base_10_divisible;
    }

    ///////////////////////
    ////
    //// Sub-Sub-Lines setup
    ////
    ///////////////////////

    view_edge_x = floor_by_digit(view.getCenter().x - (view.getSize().x / 2));
    view_edge_y = floor_by_digit(view.getCenter().y - (view.getSize().y / 2));

    // this value determines horizontal line spacing
    base_10_divisible = get_base_10_divisible(view.getSize().y / 10);

    horizontal_count =  view.getSize().y /  base_10_divisible;

    for (int i = 0; i < horizontal_count + 1; i++) {
        // horizontal sub-lines positioning
        sf::VertexArray sub_horizontal(sf::PrimitiveType::Lines, 2);

        sub_horizontal[0].color = sf::Color(150, 150, 150, calc_aplha(horizontal_count));
        sub_horizontal[1].color = sf::Color(150, 150, 150, calc_aplha(horizontal_count));


        sub_horizontal[0].position = { view.getCenter().x - (view.getSize().x / 2.f), view_edge_y };
        sub_horizontal[1].position = { view.getCenter().x + (view.getSize().x / 2.f), view_edge_y };

        // add to be drawn
        m_lines.push_back(sub_horizontal);

        // update x pos for next verticle line
        view_edge_y += base_10_divisible;
    }

    // this value determines verticle line spacing
    base_10_divisible = get_base_10_divisible(view.getSize().x / 10);

    verticle_count =  view.getSize().x /  base_10_divisible;
    for (int i = 0; i < verticle_count + 1; i++) {
        // vertical sub-lines positioning
        sf::VertexArray sub_vertical(sf::PrimitiveType::Lines, 2);

        sub_vertical[0].color = sf::Color(150, 150, 150, calc_aplha(verticle_count));
        sub_vertical[1].color = sf::Color(150, 150, 150, calc_aplha(verticle_count));

        sub_vertical[0].position = {view_edge_x, view.getCenter().y - (view.getSize().y / 2.f)};
        sub_vertical[1].position = {view_edge_x, view.getCenter().y + (view.getSize().y / 2.f)};

        // add to be drawn
        m_lines.push_back(sub_vertical);

        // update x pos for next verticle line
        view_edge_x += base_10_divisible;
    }

    ///////////////////////
    ////
    //// Origin-Lines setup
    ////
    ///////////////////////

    m_origin_horizontal[0].position = { view.getCenter().x - (view.getSize().x / 2.f), 0.f };
    m_origin_horizontal[1].position = { view.getCenter().x + (view.getSize().x / 2.f), 0.f };

    m_origin_verticle[0].position = { 0.f, view.getCenter().y - (view.getSize().y / 2.f) };
    m_origin_verticle[1].position = { 0.f, view.getCenter().y + (view.getSize().y / 2.f) };

    m_lines.push_back(m_origin_verticle);
    m_lines.push_back(m_origin_horizontal);
}

constexpr float GridSpace::floor_by_digit(int64_t n_)  {
    //if (abs(n_) < 10 || !n_ ) return 0;      // avoid log(0)
    if (!n_) return 0;

    int digit_ = log10(abs(n_));
    return ( n_ / (uint)pow(10.f, digit_)) * pow(10, digit_);
}

constexpr int GridSpace::get_base_10_divisible(const int64_t n_)
{
    //if (abs(n_) < 10 || !n_ ) return 0;      // avoid log(0)
    if (!n_) return 0;

    return pow(10, ((int)log10(abs(n_))));
}

constexpr u_char GridSpace::calc_aplha(int line_count) {
    if (!line_count) return 0;      // avoid div_by0
    return 255 / sqrt(line_count);
}

const std::vector<sf::VertexArray> &GridSpace::getGridLines() {
    return m_lines;
}





