#include "GuiTools.h"
#include "../GridSpace.h"

void GuiTools::GridStats() {
    ImGui::Begin("Grid Stats", &m_GridStats_active, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::TextColored(sf::Color::Red, "drawing to %s", m_current_world->m_name.c_str());
    ImGui::SeparatorText("Line's");

    ImGui::Text("total count: %u", GridSpace::getGridLines().size());

    const sf::VertexArray& line = GridSpace::getGridLines()[0];
/*    for (int i = 0; i < line.getVertexCount(); i++)
    {
        ImGui::Text("line pos");
        ImGui::Text("x: %f, y: %f",line[i].position.x, line[i].position.y);
    }*/

    ImGui::End();
}

