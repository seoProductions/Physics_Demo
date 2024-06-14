#include "GuiTools.h"

 void GuiTools::init(sf::RenderWindow* window_, WorldSpace* world_)
 {
    m_window = window_;
    m_current_world = world_;

    m_Properties_active = true;
    m_Settings_active   = false;
    m_DevTools_active   = true;

    m_MouseStats_active = false;
    m_ViewStats_active  = true;
}


void GuiTools::updateGUI() {

    // TOP LEVEL

    if (m_Properties_active)
        Properties();
    if (m_DevTools_active)
        DevTools();
    if (m_Settings_active)
        Settings();

    // NESTED

    if (m_MouseStats_active)
        MouseStats();
    if (m_ViewStats_active)
        ViewStats();
}

void GuiTools::Properties() {

}

void GuiTools::DevTools() {

    ImGui::Begin("Developer Tools", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::TextColored(ImColor(163, 211, 155), "Current World is: %s", m_current_world->m_name.c_str());

    if (ImGui::Button("Mouse Stats"))       { m_MouseStats_active = !m_MouseStats_active; }
    if (ImGui::Button("World View Stats"))  { m_ViewStats_active  = !m_ViewStats_active ; }

    ImGui::End();
}

void GuiTools::Settings() {

}
