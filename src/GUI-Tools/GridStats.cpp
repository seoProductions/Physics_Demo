#include "GuiTools.h"
#include "../GridSpace.h"

void GuiTools::GridStats() {
    ImGui::Begin("Grid Stats", &m_GridStats_active, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::TextColored(sf::Color::Red, "drawing to %s", m_current_world->m_name.c_str());

    ImGui::SeparatorText("Line's");
    ImGui::Text("TOTAL COUNT: %u", GridSpace::getGridLines().size());
    ImGui::Text("text info on line position %s", (GridSpace::font_available()) ? " rendered SUCCESSFULLY " : " FAILED to render");

    ImGui::SeparatorText("Debug Stack");

    if (GridSpace::getDebugInfo().size() >= 12)  // avoid segmentation fault
    {
        // generate iterator
        std::vector<float>::const_iterator info = GridSpace::getDebugInfo().cbegin();

        ImGui::Text("first sub-line x-position starts at:  %f", *info++);
        ImGui::Text("      sub-line x-axis interval value: %f", *info++);
        ImGui::Text("TOTAL sub-line x-axis count:          %f", *info++);
        ImGui::Text("first sub-line y-position starts at:  %f", *info++);
        ImGui::Text("      sub-line y-axis interval value: %f", *info++);
        ImGui::Text("TOTAL sub-line y-axis count:          %f", *info++);

        ImGui::Text("first sub-sub-line x-position starts at:  %f", *info++);
        ImGui::Text("      sub-sub-line x-axis interval value: %f", *info++);
        ImGui::Text("TOTAL sub-sub-line x-axis count:          %f", *info++);
        ImGui::Text("first sub-sub-line y-position starts at:  %f", *info++);
        ImGui::Text("      sub-sub-line y-axis interval value: %f", *info++);
        ImGui::Text("TOTAL sub-sub-line y-axis count:          %f", *info++);
    }
    else
    {
        ImGui::Text("Debug-Vector does not contain required info. Please report this to the developer!");
    }


    //more info about positioning (just for debugging , can be removed)

//    const sf::VertexArray& line = GridSpace::getGridLines()[0];
    /*    for (int i = 0; i < line.getVertexCount(); i++)
    {
        ImGui::Text("line pos");
        ImGui::Text("x: %f, y: %f",line[i].position.x, line[i].position.y);
    }*/

    ImGui::End();
}

