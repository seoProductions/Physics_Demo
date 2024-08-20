#ifndef PHYSICS_DEMO_WORLDSPACE_HPP
#define PHYSICS_DEMO_WORLDSPACE_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include "Entity/Entity.hpp"
#include "Random/random.hpp"

// credit : https://github.com/ilqvya/random
// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

/////////////////////////////////////////////////////////////////////////
////
////    WorldSpace is a class that stores helpful world data
////    Serves as a base for each interactive world
////
/////////////////////////////////////////////////////////////////////////

class WorldSpace {
public:
    WorldSpace() = default;
    WorldSpace(const std::string& name);

    //////////////////////
    ////
    //// World Behavior
    ////
    //////////////////////
    static void initBehavior(std::array<WorldSpace, 4>&);         // define unique behavior for each given world

    // FIXME: pass pos_ by reference please c++?
    // to be initialized with initBehavior()
    std::function< void(const sf::Vector2f pos_)>
                            spawnEntity;     // available when un-paused & active
    std::function< void()>  start;
    std::function< void()>  update;
    std::function< void()>  reset;

    [[maybe_unused]]
    void UnPause();
    void Pause();
    void TogglePause();
    void Activate();
    void DeActivate();

    bool active() const;
    bool paused() const;


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

#endif //PHYSICS_DEMO_WORLDSPACE_HPP