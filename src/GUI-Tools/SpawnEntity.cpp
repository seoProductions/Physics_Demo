#include "GuiTools.h"

////////////////////////////////////////
////
//// Depreciated and will be deleted
////  Implementation for GuiTools.h
////
////////////////////////////////////////

void GuiTools::spawnEntity() {
    Entity entity_;

    switch (m_tool_shape) {
        case (rectangle):
            entity_.m_shape = std::make_shared<sf::RectangleShape>(
                    sf::Vector2f(Random::get(50.f, 200.f), Random::get(50.f, 200.f)));
            entity_.m_name = "rectangle";
            break;
        case (triangle):
            entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(50.f, 100.f), 3);
            entity_.m_name = "triangle";
            break;
        case (pentagon):
            entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(50.f, 100.f), 5);
            entity_.m_name = "pentagon";
            break;
        case (hexagon):
            entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(50.f, 100.f), 6);
            entity_.m_name = "hexagon";
            break;
        default:
            break;

    }

    // Add RigidBody attribute on conditions
    float mass_ = sqrt(entity_.m_shape->getLocalBounds().width + entity_.m_shape->getLocalBounds().width);

    entity_.m_RigidBody = std::make_shared<RigidBody>(m_current_world->m_worldview.getCenter() * -1.f, mass_);
    if (entity_.m_shape)
        entity_.m_RigidBody->attachObject(entity_.m_shape);
    entity_.m_RigidBody->setVelocity(sf::Vector2f(3402, 4));

    /*// triangle set-up
    // using crazy pointer cast
    // depreciated
    std::shared_ptr<sf::ConvexShape> triangle = std::dynamic_pointer_cast<sf::ConvexShape>(entity_.m_shape);
    if (triangle)
    {
        triangle->setPoint(0, sf::Vector2f(0.f, 0.f));
        triangle->setPoint(1, sf::Vector2f(50.f, -100.f));
        triangle->setPoint(2, sf::Vector2f(100.f, 0.f));
    }*/

    entity_.m_shape->setFillColor(sf::Color::Transparent);
    entity_.m_shape->setOutlineThickness(5.f);
    entity_.m_shape->setOutlineColor(sf::Color::Transparent);
    entity_.m_shape->setFillColor(
            sf::Color(Random::get(100, 255), Random::get(100, 255), Random::get(100, 255)));
    m_current_world->m_entity_list.push_back(entity_);      // add to entity list
}
/*void inline WorldSpace::update() {

    // Update RigidBod
    for (auto& entity : m_entity_list)
    {
        if (entity.m_RigidBody)
            entity.m_RigidBody->update();
    }
}*/

