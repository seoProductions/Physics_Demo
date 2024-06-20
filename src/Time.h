#ifndef SANDY_TIME_H
#define SANDY_TIME_H
#include <SFML/Graphics.hpp>
#include <algorithm> //std::clamp as of c++ 17
#include <cmath>     //truncf()

class Time {
private:
    //constants
    static constexpr
    float LOW_LIMIT  = 0.0167f; // in seconds

    static constexpr
    float HIGH_LIMIT = 1.f;     // in seconds

    static constexpr
    float fps_delay  = 0.2f;    // in seconds

    static inline sf::Clock clock;
    static inline sf::Time  sfml_time;

    static inline float     delta_time = LOW_LIMIT;
    static inline float     fps        = 0;    //frames per second

    // for calculating fps
    static inline sf::Clock timer;

public:

    //getters
    static float& getFps()              { return fps; }
    static float& getDeltaTime()        { return delta_time;}
    static sf::Time& getSFMLTime()      { return sfml_time; }

    //returns delta time after updating
    static float& updateDeltaTime()   {

        sfml_time   = clock.restart();
        delta_time  = sfml_time.asSeconds();

        //bounds on delta time
        //delta_time = std::clamp(delta_time, LOW_LIMIT, HIGH_LIMIT);

        //update fps based on fps_delay
        if (timer.getElapsedTime().asSeconds() > fps_delay) {
            timer.restart();
            fps = truncf(1 / delta_time);
        }
        return delta_time;
    }
};


#endif //SANDY_TIME_H
