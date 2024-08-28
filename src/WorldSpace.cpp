#include "WorldSpace.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++20-extensions"
WorldSpace::WorldSpace(const std::string &name) {
    m_isActive  = false;
    m_isPaused  = true;
    m_name      = name;
    m_camera.getView().setCenter( { 0.f, 0.f });
}

/*WorldSpace& WorldSpace::operator= (const WorldSpace& world_)   // copy assign
{
    this->m_name        = world_.m_name;
    this->m_camera      = world_.m_camera;
    this->m_isActive    = world_.m_isActive;
    this->m_isPaused    = world_.m_isPaused;
    this->spawnEntity   = world_.spawnEntity;
    this->start         = world_.start;
    this->reset         = world_.reset;
    this->update        = world_.update;
}*/


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

#include "GUI-Tools/GuiTools.hpp"

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

        /////////////////////
        ////
        ////    INIT Shape
        ////
        /////////////////////

        switch (GuiTools::m_tool_shape) {
            case (GuiTools::rectangle):
                entity_.m_shape = std::make_shared<sf::RectangleShape>(
                        sf::Vector2f(Random::get(40.f, 80.f), Random::get(40.f, 80.f)));
                entity_.m_name = "rectangle";
                break;
            case (GuiTools::triangle):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(40.f, 80.f), 3);
                entity_.m_name = "triangle";
                break;
            case (GuiTools::pentagon):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(40.f, 80.f), 5);
                entity_.m_name = "pentagon";
                break;
            case (GuiTools::hexagon):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(40.f, 80.f), 6);
                entity_.m_name = "hexagon";
                break;
            default:
                break;
        }
        // shape's position over-ridden by any existing [m_body]

        entity_.m_shape->setOutlineThickness(5.f);
        entity_.m_shape->setOutlineColor(sf::Color::Transparent);
        entity_.m_shape->setOrigin(entity_.m_shape->getGlobalBounds().height / 2,
                                   entity_.m_shape->getGlobalBounds().width / 2);
        entity_.m_shape->setFillColor(
                Random::get({ sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::White, sf::Color::Cyan })
        );

        //////////////////////////////////
        ////
        ////    INIT Kinematic Attribute
        ////
        /////////////////////////////////
        // TODO INIT KINETAMIC PROPERTIES (ATTACHMENTS)
        entity_.m_body = std::make_shared<KinematicBody>(pos_);

        // Attach shape previously created. This will sync changes in the Transform
        auto body = std::dynamic_pointer_cast<KinematicBody>(entity_.m_body);

        if (!body) return;  // avoid nullptr
        body->attachObject(entity_.m_shape);    // TODO typename pointer-cast?
        body->setVelocity       ({ Random::get( -50.f, 50.f), Random::get( 50.f, 200.f )});
        body->setAcceleration   ({ Random::get( -10.f, 10.f), Random::get( 0.f, 10.f )});
    };
    Kinematics.start = [&Kinematics]() {    if (!Kinematics.m_isActive) return;
        // TODO SET DIFFERENT KINEMATIC STARTING VALUES - mabye
        Kinematics.spawnEntity({ -400.f, 0.f });
        Kinematics.spawnEntity({ -300.f, 0.f });
        Kinematics.spawnEntity({ -200.f, 0.f });
        Kinematics.spawnEntity({ -100.f, 0.f });
        Kinematics.spawnEntity({ 0.f, 0.f });
        Kinematics.spawnEntity({ 100.f, 0.f });
        Kinematics.spawnEntity({ 200.f, 0.f });
        Kinematics.spawnEntity({ 300.f, 0.f });
        Kinematics.spawnEntity({ 400.f, 0.f });
    };
    Kinematics.update = [&Kinematics]() {   if (!Kinematics.m_isActive) return;

        for (const auto& entity : Kinematics.m_entity_list)
        {
            if (!entity.m_body) continue;

            // Default action
            entity.m_body->update();
        }
    };
    Kinematics.reset  = [&Kinematics]() {   if (!Kinematics.m_isActive) return;

        Kinematics.m_entity_list.clear();
        Kinematics.start();
    };



    ///////////////////////////////
    ////
    //// Forces World Behavior
    ////
    ///////////////////////////////

    Forces.spawnEntity = [&Forces](const sf::Vector2f pos_) {   if (!Forces.m_isActive) return;

        Forces.m_entity_list.emplace_back(Entity());    // vector is given ownership of this Entity
        Entity& entity_ = Forces.m_entity_list.back();   // generate a reference to this entity, we will be setting it up

        /////////////////////
        ////
        ////    INIT Shape
        ////
        /////////////////////

        switch (GuiTools::m_tool_shape) {
            case (GuiTools::rectangle):
                entity_.m_shape = std::make_shared<sf::RectangleShape>(
                        sf::Vector2f(Random::get(40.f, 80.f), Random::get(40.f, 80.f)));
                entity_.m_name = "rectangle";
                break;
            case (GuiTools::triangle):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(40.f, 80.f), 3);
                entity_.m_name = "triangle";
                break;
            case (GuiTools::pentagon):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(40.f, 80.f), 5);
                entity_.m_name = "pentagon";
                break;
            case (GuiTools::hexagon):
                entity_.m_shape = std::make_shared<sf::CircleShape>(Random::get(40.f, 80.f), 6);
                entity_.m_name = "hexagon";
                break;
            default:
                break;
        }
        // shape's position over-ridden by any existing [m_body]

        entity_.m_shape->setFillColor(sf::Color::Transparent);
        entity_.m_shape->setOutlineThickness(5.f);
        entity_.m_shape->setOutlineColor(sf::Color::Transparent);
        entity_.m_shape->setFillColor(
                sf::Color(Random::get(100, 255), Random::get(100, 255), Random::get(100, 255)));

        //////////////////////////////////
        ////
        ////    INIT Kinematic Attribute TODO
        ////
        /////////////////////////////////
        // TODO INIT KINETAMIC PROPERTIES (ATTACHMENTS)
        entity_.m_body = std::make_shared<KinematicBody>(pos_);

        // Attach shape previously created. This will sync changes in the Transform
        auto body = std::dynamic_pointer_cast<KinematicBody>(entity_.m_body);

        if (!body) return;  // avoid nullptr
        body->attachObject(entity_.m_shape);    // TODO typename pointer-cast?
        body->setVelocity       ({ Random::get( -50.f, 50.f), Random::get( 50.f, 200.f )});
        body->setAcceleration   ({ Random::get( -10.f, 10.f), Random::get( 0.f, 10.f )});
    };
    Forces.start = [&Forces]() {    if (!Forces.m_isActive) return;
        // TODO SET DIFFERENT RIGID STARTING VALUES - mabye
        Forces.spawnEntity({ -400.f, 0.f });
        Forces.spawnEntity({ -300.f, 0.f });
        Forces.spawnEntity({ -200.f, 0.f });
        Forces.spawnEntity({ -100.f, 0.f });
        Forces.spawnEntity({ 0.f, 0.f });
        Forces.spawnEntity({ 100.f, 0.f });
        Forces.spawnEntity({ 200.f, 0.f });
        Forces.spawnEntity({ 300.f, 0.f });
        Forces.spawnEntity({ 400.f, 0.f });
    };
    Forces.update = [&Forces]() {   if (!Forces.m_isActive) return;

        for (const auto& entity : Forces.m_entity_list)
        {
            if (!entity.m_body) continue;

            // Default action
            entity.m_body->update();
        }
    };
    Forces.reset  = [&Forces]() {   if (!Forces.m_isActive) return;

        Forces.m_entity_list.clear();
        Forces.start();
    };
}

#pragma clang diagnostic pop