
#ifndef PHYSICS_DEMO_CAMERA_HPP
#define PHYSICS_DEMO_CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "Time.hpp"

//////////////////////////////////////////////////////////////////////////////
////
////  Wrapper for sf::View that implements movement and zoom functionality
////
//////////////////////////////////////////////////////////////////////////////

class Camera {
public:
    Camera();

    // invoked at every frame
    void updateSize();
    void updateCenter();

    void setCenterTarget(const sf::Vector2f& );     // automatically update status
    void setSizeTarget  (const sf::Vector2f& );     // automatically update status
    void moveCenterTarget(const sf::Vector2f& );    // move
    void moveSizeTarget  (float &&);                // shrink / grow

    sf::View& getView();

private:
    sf::View    m_view;

    sf::Vector2f    m_target_size;  // TODO set single float for scale only
    sf::Vector2f    m_target_center;

    //////////////////////
    ////
    //// Constants
    ////
    //////////////////////

    const sf::Vector2f m_max_size { 10'000.f, 10'000.f };
    const sf::Vector2f m_min_size { 100.f, 100.f };

    const sf::Vector2f m_max_center { 10'000.f, 10'000.f };
    const sf::Vector2f m_min_center { -10'000.f, -10'000.f };

    //////////////////////
    ////
    //// Helper Functions
    ////
    //////////////////////

    // clamp
    //https://stackoverflow.com/questions/427477/fastest-way-to-clamp-a-real-fixed-floating-point-value
    static constexpr float clamp(float d, float min, float max);

    bool m_is_updating_center;
    bool m_is_updating_size;
};


#endif //PHYSICS_DEMO_CAMERA_HPP
