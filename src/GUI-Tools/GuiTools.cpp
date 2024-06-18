#include "GuiTools.h"

/////////////////////////////////////////
////
//// GUI Implemented using Dear-ImGui
////
/////////////////////////////////////////

 void GuiTools::init(sf::RenderWindow* window_, WorldSpace* world_, std::vector<WorldSpace>& world_list_)
 {
    m_window = window_;
    m_world_list = world_list_;
    m_current_world = world_;

    m_Entity_Properties_active = false;
    m_World_Properties_active = false;
    m_Settings_active   = false;
    m_DevTools_active   = false;

    m_MouseStats_active = false;
    m_ViewStats_active  = false;
    m_GridStats_active  = false;

}


void GuiTools::updateGUI() {

    ///////////////////////
    ////
    //// Main Menu Bar
    ////
    ///////////////////////

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::Button("Motion"))
        {
            m_current_world->m_isActive = false;
            m_current_world = &m_world_list[0];
            m_current_world->m_isActive = true;
        }

        if (ImGui::Button("Forces"))
        {

            m_current_world->m_isActive = false;
            m_current_world = &m_world_list[1];
            m_current_world->m_isActive = true;
        }

        if (ImGui::Button("Rotation"))
        {

            m_current_world->m_isActive = false;
            m_current_world = &m_world_list[2];
            m_current_world->m_isActive = true;
        }

        ImGui::TextColored(sf::Color(211,122,56, 250), "More");

        if (ImGui::Button("Entity Info")) { m_Entity_Properties_active = !m_Entity_Properties_active; }
        if (ImGui::Button("World Info")) { m_World_Properties_active = !m_World_Properties_active; }
        if (ImGui::Button("Dev-Tools"))  { m_DevTools_active = !m_DevTools_active; }
        if (ImGui::Button("Settings"))   { m_Settings_active = !m_Settings_active; }

        ImGui::EndMainMenuBar();
    }

    ///////////////////////
    ////
    //// ToolBar
    ////
    ///////////////////////

    auto toolbarFlags = static_cast<ImGuiWindowFlags_>(ImGuiWindowFlags_NoScrollWithMouse |
                                                                    ImGuiWindowFlags_NoSavedSettings   |ImGuiWindowFlags_AlwaysAutoResize  |
                                                                    ImGuiWindowFlags_NoCollapse);
    ImGui::Begin("Tools", nullptr, toolbarFlags);
    if (ImGui::Selectable("Rectangle"))
    {
        m_tool_shape = rectangle;
        spawnEntity();
    }
    if (ImGui::Selectable("Circle"))
    {
        m_tool_shape = circle;
        spawnEntity();
    }
    if (ImGui::Selectable("Triangle"))
    {
        m_tool_shape = triangle;
        spawnEntity();
    }
    if (ImGui::Selectable("Pentagon"))
    {
        m_tool_shape = pentagon;
        spawnEntity();
    }
    if (ImGui::Selectable("Hexagon"))
    {
        m_tool_shape = hexagon;
        spawnEntity();
    }
    ImGui::End();


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
}


void GuiTools::Entity_Properties() {
    ImGui::Begin("Entity Properties", &m_Entity_Properties_active, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::BeginMenuBar()) {
        ImGui::Button("Select");
        ImGui::Button("Delete");
        ImGui::EndMenuBar();
    }
    ImGui::End();
}

void GuiTools::World_Properties() {
    ImGui::Begin("World Properties", &m_Entity_Properties_active, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::BeginMenuBar()) {
        ImGui::Button("Select");
        ImGui::Button("Delete");
        ImGui::EndMenuBar();
    }

    ImGui::LabelText("###Entity count" ," %zu total Entities", m_current_world->m_entity_list.size());

    for (auto& entity : m_current_world->m_entity_list)
    {
        ImGui::Text(entity.m_name.c_str());
    }
    ImGui::End();
}


void GuiTools::DevTools() {

    ImGui::Begin("Developer Tools", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::TextColored(ImColor(163, 211, 155), "Current World is: %s", m_current_world->m_name.c_str());

    if (ImGui::Button("Mouse Stats"))       { m_MouseStats_active = !m_MouseStats_active; }
    if (ImGui::Button("World View Stats"))  { m_ViewStats_active  = !m_ViewStats_active ; }
    if (ImGui::Button("Grid Stats"))        { m_GridStats_active  = !m_GridStats_active ; }

    ImGui::End();
}

void GuiTools::Settings() {

}
