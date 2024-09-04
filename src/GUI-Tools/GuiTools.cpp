#include "GuiTools.hpp"

/////////////////////////////////////////
////
//// GUI Implemented using Dear-ImGui
////
/////////////////////////////////////////

 void GuiTools::init(sf::RenderWindow* window_, WorldSpace** world_, std::array<WorldSpace, 4>* const world_list_)
 {
    m_window = window_;
    m_world_list = world_list_;
    m_current_world_source = world_;      // points to the same world in main.cpp
    m_current_world = *m_current_world_source;  // stores current world

    m_Entity_Properties_active = false;
    m_World_Properties_active = false;
    m_Settings_active   = false;
    m_DevTools_active   = false;

    m_MouseStats_active = false;
    m_ViewStats_active  = false;
    m_GridStats_active  = false;
    m_TimeStats_active  = false;

    m_enabled_world_delay = false;

}


void GuiTools::updateGUI() {

    ///////////////////////
    ////
    //// Main Menu Bar
    ////
    ///////////////////////

    // future me here: I ran into a ton of trouble getting the current_world here and from main.cpp synced up.
    // I resorted to using iterators as means of avoiding copy construction and reference management.
    if (ImGui::BeginMainMenuBar())
    {
        // handy structured binding
        auto& [Kinematics, Forces, Torque, Sandbox] = *m_world_list;
        if (ImGui::Button(Kinematics.m_name.c_str()))
        {
            m_current_world->Activate();
            m_current_world->Pause();
            *m_current_world_source = m_world_list->begin();     // update ptr
            m_current_world = *m_current_world_source;
            m_current_world->Activate();
            m_current_world->Pause();
        }
        if (ImGui::Button(Forces.m_name.c_str()))
        {
            m_current_world->DeActivate();
            m_current_world->Pause();
            *m_current_world_source = m_world_list->begin() + 1;     // update ptr
            m_current_world = *m_current_world_source;
            m_current_world->Activate();
            m_current_world->Pause();
        }

        if (ImGui::Button(Torque.m_name.c_str()))
        {
            m_current_world->DeActivate();
            m_current_world->Pause();
            *m_current_world_source = m_world_list->begin() + 2;     // update ptr
            m_current_world = *m_current_world_source;
            m_current_world->Activate();
            m_current_world->Pause();
        }

        if (ImGui::Button(Sandbox.m_name.c_str()))
        {
            m_current_world->DeActivate();
            m_current_world->Pause();
            *m_current_world_source = m_world_list->begin() + 3;     // update ptr
            m_current_world = *m_current_world_source;
            m_current_world->Activate();
            m_current_world->Pause();
        }

        ImGui::TextColored(sf::Color(211,122,56, 250), "More");

        // toggle buttons
        if (ImGui::Button("Entity Info")) { m_Entity_Properties_active = !m_Entity_Properties_active; }
        if (ImGui::Button("World Info")) { m_World_Properties_active = !m_World_Properties_active; }
        if (ImGui::Button("Dev-Tools"))  { m_DevTools_active = !m_DevTools_active; }
        if (ImGui::Button("Settings"))   { m_Settings_active = !m_Settings_active; }

        ImGui::EndMainMenuBar();
    }



    ///////////////////////
    ////
    //// Top-Level Windows
    ////
    ///////////////////////

    if (m_Entity_Properties_active)
        Entity_Properties();
    if (m_World_Properties_active)
        World_Properties();
    if (m_DevTools_active)
        DevTools();
    if (m_Settings_active)
        Settings();

    ////////////////////////
    ////
    //// Nested-Level Windows
    ////
    ///////////////////////

    if (m_MouseStats_active)
        MouseStats();
    if (m_ViewStats_active)
        ViewStats();
    if (m_GridStats_active)
        GridStats();
    if (m_TimeStats_active)
        TimeStats();

    ///////////////////////////////////
    ////
    //// ToolBar (available if paused)
    ////
    ///////////////////////////////////
    if (m_current_world->paused()) return;

    auto toolbarFlags = static_cast<ImGuiWindowFlags_>(ImGuiWindowFlags_NoScrollWithMouse |
                                                       ImGuiWindowFlags_NoSavedSettings   |ImGuiWindowFlags_AlwaysAutoResize  |

                                                       ImGuiWindowFlags_NoCollapse);
    // Switch Case-Statements would disallow the button creation inside the condition
    ImGui::Begin("Tools", nullptr, toolbarFlags);
    if (ImGui::Selectable("Rectangle"))
    {
        m_tool_shape = rectangle;
        m_current_world->spawnEntity({ 0.f, 0.f});
    }
    if (ImGui::Selectable("Triangle"))
    {
        m_tool_shape = triangle;
        m_current_world->spawnEntity({ 0.f, 0.f});
    }
    if (ImGui::Selectable("Pentagon"))
    {
        m_tool_shape = pentagon;
        m_current_world->spawnEntity({ 0.f, 0.f});

    }
    if (ImGui::Selectable("Hexagon"))
    {
        m_tool_shape = hexagon;
        m_current_world->spawnEntity({ 0.f, 0.f});

    }
    ImGui::End();
}


void GuiTools::Entity_Properties() {

    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    ImGui::Begin("Entity Properties", &m_Entity_Properties_active, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::BeginMenuBar()) {    // TODO FIX THIS
        ImGui::Button("Select");
        ImGui::Button("Delete");
        ImGui::EndMenuBar();
    }

    // TODO TEMPORARY -> Show only 1 selected
    /*if (!m_current_world->m_entity_list.empty()) {
        if (m_current_world->m_entity_list[0].m_RigidBody)
        {
            ImGui::SeparatorText("RigidBody-Properties");

            // generate reference to current body
            RigidBody& body = *m_current_world->m_entity_list[0].m_RigidBody;

            ImGui::Text("position x: %f", body.getPosition().x);
            ImGui::Text("position y: %f", body.getPosition().y);
            ImGui::Text("velocity x: %f", body.getVelocity().x);
            ImGui::Text("velocity y: %f", body.getVelocity().y);
            ImGui::Text("acceleration x: %f", body.getAcceleration().x);
            ImGui::Text("acceleration y: %f", body.getAcceleration().y);
            ImGui::Text("momentum x: %f", body.getMomentum().x);
            ImGui::Text("momentum y: %f", body.getMomentum().y);
            ImGui::Text("mass: %f grams", body.getMass());
        }
    }*/


    ImGui::End();
}

void GuiTools::World_Properties() {
    ImGui::Begin("World Properties", &m_Entity_Properties_active, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("world: %s: ", m_current_world->m_name.c_str());
    ImGui::TextColored( ImColor(179, 200, 200),
                        "World is %s and %s", (m_current_world->active()) ? "ACTIVE": "NOT ACTIVE", (m_current_world->paused()) ? "PAUSED" : "RUNNING");
    if (ImGui::SmallButton("Pause/Unpause")) m_current_world->TogglePause();
    if (ImGui::SmallButton("RESET")) m_current_world->reset();
    if (ImGui::SmallButton("Back to Origin"))
    {
        m_current_world->m_camera.setCenterTarget   ( { 0.f, 0.f } );
        m_current_world->m_camera.setSizeTarget     ( { 1'000.f, 1'000.f } );
    }
    ImGui::LabelText("###Entity count" ," %zu total Entities", m_current_world->m_entity_list.size());

    ImGui::End();
}


void GuiTools::DevTools() {

    ImGui::Begin("Developer Tools", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::TextColored(ImColor(163, 211, 155), "Current World is: %s", m_current_world->m_name.c_str());

    if (ImGui::Button("Time Stats"))        { m_TimeStats_active  = !m_TimeStats_active ; }
    if (ImGui::Button("Mouse Stats"))       { m_MouseStats_active = !m_MouseStats_active; }
    if (ImGui::Button("World View Stats"))  { m_ViewStats_active  = !m_ViewStats_active ; }
    if (ImGui::Button("Grid Stats"))        { m_GridStats_active  = !m_GridStats_active ; }

    ImGui::End();
}

void GuiTools::Settings() {

}
