
#include "GuiTools.hpp"
#include "../Time.hpp"

void GuiTools::TimeStats()
{
    ImGui::Begin("Time Stats", &m_TimeStats_active, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SeparatorText("delta time:");
    ImGui::Text(" %f ", Time::getDeltaTime());
    ImGui::SeparatorText("frames per second:");
    ImGui::Text(" %f ", Time::getFps());
    ImGui::SeparatorText("more:");
    // just for fun lol
    if (ImGui::Button("x1"))   Time::scale = 2.f;
    if (ImGui::Button("x2"))   Time::scale = 2.f;
    if (ImGui::Button("x5"))  Time::scale = 5.f;

    ImGui::End();
}

