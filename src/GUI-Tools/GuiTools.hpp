
#ifndef PHYSICS_DEMO_GUITOOLS_HPP
#define PHYSICS_DEMO_GUITOOLS_HPP

#include <imgui.h>
#include <memory>

#include "../DragHandler.hpp"
#include "../WorldSpace.hpp"
#include "../Random/random.hpp"

// credit : https://github.com/ilqvya/random
// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;


////////////////////////////////////////////////////////////////
////
////  Class that implements all Gui functionality and logic
////
////////////////////////////////////////////////////////////////

class GuiTools {
public:
    static void init(sf::RenderWindow*, WorldSpace*, std::array<WorldSpace, 4>&);
    static void updateGUI();        // invoked every frame

    // conditional windows
    inline static bool m_DevTools_active;
    inline static bool m_Settings_active;
    inline static bool m_Entity_Properties_active;
    inline static bool m_World_Properties_active;

    // toolbar status
    enum tool
            { rectangle = 0,
              triangle,
              pentagon,
              hexagon,
              select,
              remove };
    inline static tool m_tool_shape = rectangle;    // entity to spawn in
    inline static tool m_tool_modify = select;      // select or remove


private:

    // main program variables - statically allocated
    inline static sf::RenderWindow* m_window;
    inline static WorldSpace*       m_current_world;
    inline static
    std::array<WorldSpace, 4>       m_world_list { };

    ////////////////
    ////
    ////    Gui
    ////
    ////////////////

    static void Entity_Properties();
    static void World_Properties();
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

    inline static bool m_GridStats_active;
    static void GridStats();    // GridStats.cpp

    inline static bool m_TimeStats_active;
    static void TimeStats();    // TimeStats.cpp

    ////////////////////////
    ////
    ////    ToolBar Logic
    ////
    ////////////////////////

    static void spawnEntity();
};


#endif //PHYSICS_DEMO_GUITOOLS_HPP
