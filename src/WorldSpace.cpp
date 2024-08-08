#include "WorldSpace.h"

WorldSpace::WorldSpace(const std::string &name) {
    m_isActive  = false;
    m_isPaused  = true;
    m_name      = name;
    m_worldview.setCenter(0.f,0.f);
}

void WorldSpace::Pause()        { m_isPaused = true; }
void WorldSpace::UnPause()      { m_isPaused = false; }
void WorldSpace::Activate()     { m_isActive = true; }
void WorldSpace::DeActivate()   { m_isActive = false; }



