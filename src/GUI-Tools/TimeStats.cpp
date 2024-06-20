
#include "GuiTools.h"
#include "../Time.h"

void GuiTools::TimeStats()
{
    ImGui::Begin("Time Stats", &m_TimeStats_active, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SeparatorText("delta time:");
    ImGui::Text(" %f ", Time::getDeltaTime());
    ImGui::SeparatorText("frames per second:");
    ImGui::Text(" %f ", Time::getFps());
    ImGui::End();
}

