#ifndef PHYSICS_DEMO_WORLDSPACE_H
#define PHYSICS_DEMO_WORLDSPACE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "Entity/Entity.h";


/////////////////////////////////////////////////////////////////////////
////
////    WorldSpace is a class that stores helpful world data
////    Serves as a base for each interactive world
////
/////////////////////////////////////////////////////////////////////////

class WorldSpace {
public:

    WorldSpace(const std::string& name);

    //////////////////////
    ////
    //// World Behavior
    ////
    //////////////////////

    std::function< void()> start();         // to be initialized outside of class
    std::function< void()> update();
    std::function< void()> end();

    void Pause();
    void UnPause();
    void Activate();
    void DeActivate();

    //////////////////////
    ////
    //// World Info
    ////
    //////////////////////

    // world entities
    std::vector<Entity> m_entity_list;

    std::string m_name;
    sf::View    m_worldview;

private:

    bool        m_isPaused;
    bool        m_isActive;


};


/*void inline WorldSpace::update() {

    // Update RigidBod
    for (auto& entity : m_entity_list)
    {
        if (entity.m_RigidBody)
            entity.m_RigidBody->update();
    }
}*/


#endif //PHYSICS_DEMO_WORLDSPACE_H
