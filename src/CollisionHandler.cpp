
#include "CollisionHandler.hpp"

bool CollisionHandler::isColliding(const sf::Shape* s1_, const sf::Shape* s2_) {
    // helper vectors
    std::vector<sf::Vector2f> normalVectors;
    sf::Vector2f temp;
    sf::Vector2f edge;

    // push normal vector for each edge of shape1
    for (int i = 0; i < s1_->getPointCount(); i++)
    {
        // avoid out of bounds, whilst using each edge of the shape
        const int i_capacity = s1_->getPointCount() - 1;

        edge =  s1_->getPoint((i + 1) % i_capacity) -
                s1_->getPoint(i);

        // normalize the normal
        temp = { edge.y, edge.x };
        temp /= sqrtf(temp.x * temp.x + temp.y * temp.y);
        normalVectors.emplace_back( temp );
    }

    // push normal vector for each edge of shape2
    for (int i = 0; i < s2_->getPointCount(); i++)
    {
        // avoid out of bounds, whilst using each edge of the shape
        const int i_capacity = s2_->getPointCount() - 1;

        edge =  s2_->getPoint((i + 1) % i_capacity) -
                s2_->getPoint(i);

        // normalize the normal
        temp = { edge.y, edge.x };
        temp /= sqrtf(temp.x * temp.x + temp.y * temp.y);
        normalVectors.emplace_back( temp );
    }

    float s1min = std::numeric_limits<float>::max();
    float s2min = std::numeric_limits<float>::max();
    float s1max = std::numeric_limits<float>::min();
    float s2max = std::numeric_limits<float>::min();

    // iterate through all normal vectors. use SAT and if separation axis is found, return false
    for (const auto& normal: normalVectors)
    {

        // find min and max projection of each shape
        // shape A
        for (int i = 0; i < s1_->getPointCount(); i++)
        {
            const float projection = dot(s1_->getPoint(i), normal);
            s1min = std::min( s1min, projection);
            s1max = std::max( s1max, projection);
        }

        // find min and max projection of each shape
        // shape B
        for (int i = 0; i < s2_->getPointCount(); i++)
        {
            const float projection = dot(s2_->getPoint(i), normal);
            s2min = std::min( s2min, projection);
            s2max = std::max( s2max, projection);
        }

        // CHECK FOR PROJECTION OVERLAP
        if ((s1min < s2max && s1min > s2min) ||
            (s2min < s1max && s2min > s1min))
            continue;   // overlap found, re-iterate this loop
        else
            return false;    // not overlapping
    }

    // at this point, the 2 shapes ARE colliding and true value is returned
    return true;
}

/*bool CollisionHandler::isColliding(const sf::Shape &s1_, const sf::Shape &s2_) {
    // helper vectors
    std::stack<sf::Vector2f> normalVectors;
    sf::Vector2f normal;
    sf::Vector2f edge;

    // push normal vector for each edge of shape1
    for (int i = 0; i < s1_.getPointCount() - 1; i++)
    {
        edge = s1_.getPoint(i + 1) - s1_.getPoint(i);
        normal = { -edge.x, edge.y };
        normalVectors.push( std::move(normal) );
    }

    // push normal vector for each edge of shape2
    for (int i = 0; i < s2_.getPointCount() - 1; i++)
    {
        edge = s2_.getPoint(i + 1) - s2_.getPoint(i);
        normal = { -edge.x, edge.y };
        normalVectors.push( std::move(normal) );
    }

    // TODO FIX THE MAX MIN SUTIATION
    float s1min = dot(s1_.getPoint(0), normalVectors.top());
    float s2min = dot(s1_.getPoint(0), normalVectors.top());
    float s1max = dot(s2_.getPoint(0), normalVectors.top());
    float s2max = dot(s2_.getPoint(0), normalVectors.top());
    sf::Vector2f axis;

    // iterate through all normal vectors. use SAT and if separation axis is found, return false
    while (!normalVectors.empty())
    {
        axis = normalVectors.top();
        normalVectors.pop();

        // find min and max projection of each shape
        // shape A
        for (int i = 0; i < s1_.getPointCount(); i++)
        {
            const float projection = dot(s1_.getPoint(i), axis);
            s1min = std::min( s1min, projection);
            s1max = std::max( s1max, projection);
        }

        // find min and max projection of each shape
        // shape B
        for (int i = 0; i < s2_.getPointCount(); i++)
        {
            const float projection = dot(s2_.getPoint(i), axis);
            s2min = std::min( s2min, projection);
            s2max = std::max( s2max, projection);
        }

        // CHECK FOR PROJECTION OVERLAP
        if ((s1min < s2max && s1min > s2min) ||
            (s2min < s1max && s2min > s1min))
            continue;   // overlap found, re-iterate this loop
        else
            return false;    // not overlapping. MTV vector is empty
    }

    // at this point, the 2 shapes ARE colliding and must be resolved.
    // the resolved
    return true;
}*/

// FIXME: BROKEN!
std::optional<sf::Vector2f> CollisionHandler::isCollidingMTV(const sf::Shape &s1_, const sf::Shape &s2_) {

    std::stack<sf::Vector2f> normalVectors;
    sf::Vector2f normal;

    // push normal vector for each edge of shape1
    for (int i = 0; i < s1_.getPointCount(); i++)
    {
        normal = s1_.getPoint(i);
        normal.x *= -1;
        normalVectors.push( normal );
    }

    // push normal vector for each edge of shape2
    for (int i = 0; i < s2_.getPointCount(); i++)
    {
        normal = s2_.getPoint(i);
        normal.x *= 1;
        normalVectors.push( normal );
    }

    // create min axis TODO
    float s1min, s2min = std::numeric_limits<float>::max();
    float s1max, s2max = std::numeric_limits<float>::min();
    sf::Vector2f axis;

    // iterate through all normal vectors. use SAT and if separation axis is found, return a null optional object
    while (!normalVectors.empty())
    {
        axis = normalVectors.top();
        normalVectors.pop();

        // find min and max projection of each shape
        // shape A
        for (int i = 0; i < s1_.getPointCount(); i++)
        {
            const float projection = dot(s1_.getPoint(i), axis);
            s1min = std::min( s1min, projection);
            s1max = std::max( s1max, projection);
        }

        // find min and max projection of each shape
        //  A
        for (int i = 0; i < s2_.getPointCount(); i++)
        {
            const float projection = dot(s2_.getPoint(i), axis);
            s2min = std::min( s2min, projection);
            s2max = std::max( s2max, projection);
        }

        // CHECK FOR PROJECTION OVERLAP
        if ((s1min < s2max && s1min < s2min) ||
            (s2min < s1max && s2min < s1min))
            continue;   // overlap found, re-iterate this loop
        else
            return std::nullopt;    // not overlapping. MTV vector is empty
    }

    // at this point, the 2 shapes ARE colliding and must be resolved.
    // the resolved
    return sf::Vector2f ( 0.f, 0.f );
}

const float CollisionHandler::dot(const sf::Vector2f &lhs, const sf::Vector2f &rhs) {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}
