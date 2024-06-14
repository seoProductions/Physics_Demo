
#ifndef PHYSICS_DEMO_GUITOOLS_H
#define PHYSICS_DEMO_GUITOOLS_H

#include "../DragHandler.h"
#include "../WorldSpace.h"
#include <imgui.h>

class GuiTools {
public:
    static void init(sf::RenderWindow*, WorldSpace*);
    static void updateGUI();        // invoked every frame

    inline static bool m_DevTools_active;
    inline static bool m_Settings_active;
    inline static bool m_Properties_active;

private:

    // main program variables - statically allocated
    inline static sf::RenderWindow* m_window;
    inline static WorldSpace*       m_current_world;

    ////////////////
    ////
    ////    Gui
    ////
    ////////////////

    static void Properties();
    static void DevTools();
    static void Settings();

    ////////////////
    ////
    ////  Nested GUI
    ////
    ////////////////

    inline static bool m_MouseStats_active;
    static void MouseStats();   // MouseStats.cpp

    inline static bool m_ViewStats_active;
    static void ViewStats();    // WorldViewStats.cpp
};


#endif //PHYSICS_DEMO_GUITOOLS_H
