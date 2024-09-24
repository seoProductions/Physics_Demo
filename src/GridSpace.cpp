
#include <cmath>
#include <imgui.h>
#include <algorithm>

#include "GridSpace.hpp"

void GridSpace::init(WorldSpace* world_, sf::RenderWindow* window_)
{
    m_current_world = world_;
    m_main_window   = window_;

    // initializing origin lines
    m_origin_verticle.  setPrimitiveType(sf::PrimitiveType::Lines);
    m_origin_horizontal.setPrimitiveType(sf::PrimitiveType::Lines);

    m_origin_verticle.  resize(2);
    m_origin_horizontal.resize(2);

    m_origin_verticle[0].color = sf::Color(126, 161, 191);
    m_origin_verticle[1].color = sf::Color(126, 161, 191);
    m_origin_horizontal[0].color = sf::Color(126, 161, 191);
    m_origin_horizontal[1].color = sf::Color(126, 161, 191);

    // initialize font
    m_font_available = false;
    if (m_font.loadFromFile("/home/seo/CLionProjects/Physics_Demo/Resources/ProggyClean.ttf"))
        m_font_available = true;
}

void GridSpace::updateGrid() {

    m_lines.clear();
    m_lines_text.clear();
    m_debug_vector.clear();

    const sf::View& view = m_current_world->m_camera.getView();

    ///////////////////////
    ////
    //// Sub-Lines setup
    ////
    ///////////////////////

    float view_edge_x = floor_by_digit( (long)(view.getCenter().x - (view.getSize().x / 2)));
    float view_edge_y = floor_by_digit( (long)(view.getCenter().y - (view.getSize().y / 2)));
    m_debug_vector.push_back(view_edge_x);


    // this value determines verticle line spacing
    int base_10_divisible = get_base_10_divisible(view.getSize().x / 2);    // take account half of world view
    m_debug_vector.push_back(base_10_divisible); // FIXME: lines dont render outside of 1000

    int verticle_count =  (int)view.getSize().x /  base_10_divisible;
    m_debug_vector.push_back(verticle_count);


    for (int i = 0; i < verticle_count + 1; i++) {
        // vertical sub-lines positioning
        sf::VertexArray sub_vertical(sf::PrimitiveType::Lines, 2);

        sub_vertical[0].color = sf::Color(150, 150, 150, calc_alpha(verticle_count));
        sub_vertical[1].color = sf::Color(150, 150, 150, calc_alpha(verticle_count));

        sub_vertical[0].position = {view_edge_x, view.getCenter().y - (view.getSize().y / 2.f)};
        sub_vertical[1].position = {view_edge_x, view.getCenter().y + (view.getSize().y / 2.f)};

        // add to be drawn
        m_lines.push_back(sub_vertical);

        if (m_font_available)
        {
            // sub-line's x position displayed as text

            sf::Text text;
            text.setFont(m_font);
            text.setCharacterSize(35);
            text.setFillColor(sf::Color(219,237,227));
            text.setString(std::to_string((int)view_edge_x));

            text.setPosition(view_edge_x, 0.f);
            clampPosToGrid(&text);

            // translate coordinates from CurrentView -> Default View
            // this ensures reliable text quality and scaling
            const sf::View defaultView = m_main_window->getDefaultView();

            text.setPosition(( m_main_window->mapPixelToCoords(
                    m_main_window->mapCoordsToPixel(text.getPosition()),
                    defaultView)));

            m_lines_text.push_back(text);
        }
        // update x pos for next verticle line and repeat
        view_edge_x += base_10_divisible;
    }

    m_debug_vector.push_back(view_edge_y);

    // this value determines horizontal line spacing
    base_10_divisible = get_base_10_divisible((long)view.getSize().y / 2);    // take account half of world view
    m_debug_vector.push_back(base_10_divisible);

    int horizontal_count =  (int)view.getSize().y /  base_10_divisible;
    m_debug_vector.push_back(horizontal_count);

    for (int i = 0; i < horizontal_count + 1; i++) {
        // horizontal sub-lines positioning
        sf::VertexArray sub_horizontal(sf::PrimitiveType::Lines, 2);

        sub_horizontal[0].color = sf::Color(150, 150, 150, calc_alpha(horizontal_count));
        sub_horizontal[1].color = sf::Color(150, 150, 150, calc_alpha(horizontal_count));


        sub_horizontal[0].position = { view.getCenter().x - (view.getSize().x / 2.f), view_edge_y };
        sub_horizontal[1].position = { view.getCenter().x + (view.getSize().x / 2.f), view_edge_y };

        // add to be drawn
        m_lines.push_back(sub_horizontal);

        if (m_font_available)
        {
            // sub-line's y position displayed as text

            sf::Text text;
            text.setFont(m_font);
            text.setCharacterSize(35);
            text.setFillColor(sf::Color(219,237,227));
            text.setString(std::to_string((int)view_edge_y));

            text.setPosition(0.f, view_edge_y);
            clampPosToGrid(&text);

            // translate coordinates from CurrentView -> Default View
            // this ensures reliable text quality and scaling
            const sf::View defaultView = m_main_window->getDefaultView();

            text.setPosition(( m_main_window->mapPixelToCoords(
                    m_main_window->mapCoordsToPixel(text.getPosition()),
                    defaultView)));

            m_lines_text.push_back(text);
        }
        // update y pos for next verticle line and repeat
        view_edge_y += base_10_divisible;
    }

    ///////////////////////
    ////
    //// Sub-Sub-Lines setup
    ////
    ///////////////////////


    view_edge_x = floor_by_digit( (long)(view.getCenter().x - (view.getSize().x / 2)) );
    view_edge_y = floor_by_digit( (long)(view.getCenter().y - (view.getSize().y / 2)));
    m_debug_vector.push_back(view_edge_x);

    // this value determines horizontal line spacing
    base_10_divisible = get_base_10_divisible((long)view.getSize().y / 20);    // take account half of a tenth of world view
    m_debug_vector.push_back(base_10_divisible);

    horizontal_count =  (int)view.getSize().y /  base_10_divisible;
    m_debug_vector.push_back(horizontal_count);

    for (int i = 0; i < horizontal_count + 1; i++) {
        // horizontal sub-lines positioning
        sf::VertexArray sub_horizontal(sf::PrimitiveType::Lines, 2);

        sub_horizontal[0].color = sf::Color(150, 150, 150, calc_alpha(horizontal_count));
        sub_horizontal[1].color = sf::Color(150, 150, 150, calc_alpha(horizontal_count));


        sub_horizontal[0].position = { view.getCenter().x - (view.getSize().x / 2.f), view_edge_y };
        sub_horizontal[1].position = { view.getCenter().x + (view.getSize().x / 2.f), view_edge_y };

        // add to be drawn
        m_lines.push_back(sub_horizontal);

        // update x pos for next verticle line
        view_edge_y += base_10_divisible;
    }
    m_debug_vector.push_back(view_edge_y);

    // this value determines verticle line spacing
    base_10_divisible = get_base_10_divisible(view.getSize().x / 20);     // take account half of a tenth of world view
    m_debug_vector.push_back(base_10_divisible);

    verticle_count =  view.getSize().x /  base_10_divisible;
    m_debug_vector.push_back(verticle_count);

    for (int i = 0; i < verticle_count + 1; i++) {
        // vertical sub-lines positioning
        sf::VertexArray sub_vertical(sf::PrimitiveType::Lines, 2);

        sub_vertical[0].color = sf::Color(150, 150, 150, calc_alpha(verticle_count));
        sub_vertical[1].color = sf::Color(150, 150, 150, calc_alpha(verticle_count));

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

///////////////////////
////
//// Math
////
///////////////////////

constexpr float GridSpace::floor_by_digit(int64_t n_)  {
    //if (abs(n_) < 10 || !n_ ) return 0;      // avoid log(0)
    if (!n_) return 0;

    int digit_ = log10(abs(n_));
    return ( n_ / (uint)pow(10.f, digit_)) * pow(10, digit_);
}

constexpr int GridSpace::get_base_10_divisible(const int64_t n_)
{
    //if (abs(n_) < 10 || !n_ ) return 0;      // avoid log(0)
    if (!n_) return 1;

    return pow(10, ((int)log10(abs(n_))));
}


constexpr u_char GridSpace::calc_alpha(int line_count) {
    if (!line_count) return 0;      // avoid div_by0
    return 255 / sqrt(line_count);
}

inline
constexpr float GridSpace::clamp(float d, float min, float max) {
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

///////////////////////
////
//// Position Clamping
////
///////////////////////

void GridSpace::clampPosToGrid(sf::Transformable* object ) {
    const sf::View& view = m_current_world->m_camera.getView();

    const int64_t left_edge_x   = view.getCenter().x - (view.getSize().x / 2);
    const int64_t right_edge_x  = view.getCenter().x + (view.getSize().x / 2);
    const int64_t down_edge_y   = view.getCenter().y - (view.getSize().y / 2);
    const int64_t up_edge_y     = view.getCenter().y + (view.getSize().y / 2);

    object->setPosition( clamp(object->getPosition().x , left_edge_x, right_edge_x),
                         clamp(object->getPosition().y , down_edge_y, up_edge_y));

}



///////////////////////
////
//// Getters
////
///////////////////////

const std::vector<sf::VertexArray> &GridSpace::getGridLines() {
    return m_lines;
}

const std::vector<sf::Text> &GridSpace::getGridLinesText() {
    return m_lines_text;
}

bool GridSpace::font_available() {
    return m_font_available;
}

std::vector<float> &GridSpace::getDebugInfo() {
    return m_debug_vector;
}






