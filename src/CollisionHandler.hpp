
#ifndef PHYSICS_DEMO_COLLISIONHANDLER_HPP
#define PHYSICS_DEMO_COLLISIONHANDLER_HPP
#include <optional>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits>
#include <math.h>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
////
////  CollisionHandler - Handles collision details among different
////    entity types. Relies on SAT theorem.
////
///////////////////////////////////////////////////////////
class CollisionHandler {
public:
    // returns true if colliding.
    [[nodiscard]] static bool isColliding(
            const sf::Shape*,
            const sf::Shape*);

    // returns Minimum Translation Vector (MTV) if the 2 shapes collide.
    [[nodiscard]] static std::optional<sf::Vector2f> isCollidingMTV(
            const sf::Shape&,
            const sf::Shape&);

    // more math!
    static
    const float dot(const sf::Vector2f&,
              const sf::Vector2f&);
};


#endif //PHYSICS_DEMO_COLLISIONHANDLER_HPP
