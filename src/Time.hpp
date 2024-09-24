#ifndef SANDY_TIME_H
#define SANDY_TIME_H
#include <SFML/Graphics.hpp>
#include <algorithm> //std::clamp as of c++ 17
#include <cmath>     //truncf()

class Time {
private:

    static inline sf::Clock clock;          // main clock in use
    static inline sf::Clock fps_timer;      //
    static inline sf::Clock world_timer;    // optional usage
    static inline sf::Clock spawn_timer;    // optional usage

    // Wrapper for a time value / interval
    static inline sf::Time  sfml_time;      // sync time between SFML-IMGUI

    ////////////////////
    ////
    ////    Constants
    ////
    ///////////////////

    //constants
    static constexpr
    float LOW_LIMIT  = 0.0167f; // in seconds

    static constexpr
    float HIGH_LIMIT = 1.f;     // in seconds

    ///////////////////////
    ////
    ////    Main members
    ////
    //////////////////////

    static inline float     delta_time = LOW_LIMIT;
    static inline float     fps        = 0;             // frames per second

    static inline float     fps_timer_delay = 0.2f;     // in seconds
    static inline float     world_timer_delay = 20.f;    // in seconds
    static inline float     spawn_timer_delay = 0.2f;   // in seconds
public:

    // why not?
    static inline float     scale      = 1;

    //returns delta time after updating
    static float& updateDeltaTime()   {

        sfml_time   = clock.restart();
        delta_time  = sfml_time.asSeconds();

        //bounds on delta time
        delta_time = std::clamp(delta_time, LOW_LIMIT, HIGH_LIMIT);

        //update fps based on fps_delay
        if (fps_timer.getElapsedTime().asSeconds() > fps_timer_delay) {
            fps_timer.restart();
            fps = truncf(1 / delta_time);
        }

        delta_time *= scale;
        return delta_time;
    }

    // returns if world_timer exceeded delay. This is so that the world can automatically reset at given intervals
    static bool worldTimerUpdate() {
        if (world_timer.getElapsedTime().asSeconds() > world_timer_delay)
        {
            world_timer.restart();
            return true;
        }
        return false;
    }

    static bool spawnTimerUpdate()
    {
        if (spawn_timer.getElapsedTime().asSeconds() > spawn_timer_delay)
        {
            spawn_timer.restart();
            return true;
        }
        return false;
    }

    // getters
    static float& getFps()              { return fps; }
    static float& getDeltaTime()        { return delta_time;}
    static sf::Time& getSFMLTime()      { return sfml_time; }

    static float& getFpsDelay()         { return fps_timer_delay; }
    static float& getWorldDelay()       { return world_timer_delay; }
    static float& getSpawnDelay()       { return spawn_timer_delay; }

};


#endif //SANDY_TIME_H
