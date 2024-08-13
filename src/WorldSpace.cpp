#include "WorldSpace.h"

WorldSpace::WorldSpace(const std::string &name) {
    m_isActive  = false;
    m_isPaused  = true;
    m_name      = name;
    m_worldview.setCenter(0.f,0.f);
}

[[maybe_unused]]
void WorldSpace::UnPause()      { m_isPaused = false; }
void WorldSpace::Pause()        { m_isPaused = true; }
void WorldSpace::Activate()     { m_isActive = true; }
void WorldSpace::DeActivate()   { m_isActive = false; }

bool WorldSpace::active() const {
    return m_isActive;
}

bool WorldSpace::paused() const {
    return m_isPaused;
}

void WorldSpace::TogglePause() {
    m_isPaused = !m_isPaused;
}

#include "GUI-Tools/GuiTools.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////    Defining all behavior for each world.
////
////    spawnEntity - defines colors/ position/ shape of transformable entity
////                    and pushes it onto std::vector m_entity_list
////    start       - defines behavior at the beginning of the program. This is invoked before the game loop
////    update      - behavior done at every frame. Unique for each world. Some worlds may update Kinematic Properties only,
////                    whilst other worlds may have more complex logic to handle. This implementation is done to achieve a
////                    demonstration feel to this project. A demo!
////    reset       - simply resets the world to its default state. Invokes start()
////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WorldSpace::initBehavior(std::array<WorldSpace, 4>& world) {
    // worlds available
    auto& [ Kinematics, Forces, Torque, Sandbox ] = world;

    ///////////////////////////////
    ////
    //// Kinematic World Behavior
    ////
    ///////////////////////////////

    Kinematics.spawnEntity = [&Kinematics](const sf::Vector2f pos_) {   if (!Kinematics.m_isActive) return;

        Kinematics.m_entity_list.emplace_back(Entity());    // vector is given ownership of this Entity
        Entity& entity_ = Kinematics.m_entity_list.back();   // generate a reference to this entity, we will be setting it up

        switch (GuiTools::m_tool_shape) {
            case (GuiTools::rectangle):
                entity_.m_shape = std::make_shared<sf::RectangleShape>(
                        sf::Vector2f(Random::get(50.f, 200.f), Random::get(50.f, 200.f)));
                entity_.m_name = "rectangle";
                break;
            case (GuiTools::triangle):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(50.f, 100.f), 3);
                entity_.m_name = "triangle";
                break;
            case (GuiTools::pentagon):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(50.f, 100.f), 5);
                entity_.m_name = "pentagon";
                break;
            case (GuiTools::hexagon):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(50.f, 100.f), 6);
                entity_.m_name = "hexagon";
                break;
            default:
                break;
        }
        entity_.m_shape->setPosition(pos_);
        entity_.m_shape->setFillColor(sf::Color::Transparent);
        entity_.m_shape->setOutlineThickness(5.f);
        entity_.m_shape->setOutlineColor(sf::Color::Transparent);
        entity_.m_shape->setFillColor(
                sf::Color(Random::get(100, 255), Random::get(100, 255), Random::get(100, 255)));

        // TODO INIT KINETAMIC PROPERTIES
    };
    Kinematics.start = [&Kinematics]() {    if (!Kinematics.m_isActive) return;
        // TODO SET DIFFERENT KINEMATIC STARTING VALUES
        Kinematics.spawnEntity({ 0, 0 });
        Kinematics.spawnEntity({ 0, 0 });
        Kinematics.spawnEntity({ 0, 0 });

    };
    Kinematics.update = [&Kinematics]() {   if (!Kinematics.m_isActive) return;
    };
    Kinematics.reset  = [&Kinematics]() {   if (!Kinematics.m_isActive) return;

        Kinematics.m_entity_list.clear();
        Kinematics.start();
};
}
