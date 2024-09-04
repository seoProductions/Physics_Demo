
#include "GuiTools.hpp"

void GuiTools::TimeStats()
{
    ImGui::Begin("Time Stats", &m_TimeStats_active, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SeparatorText("delta time:");
    ImGui::Text(" %f ", Time::getDeltaTime());
    ImGui::SeparatorText("frames per second:");
    // Color:  red - low fps,  green - fast fps.
    ImGui::TextColored(ImColor( std::clamp(255 - (2 * Time::getFps()), 0.f, 255.f),
                                std::clamp( 2 * Time::getFps(), 0.f, 255.f),     0.f), " %f", Time::getFps());
    ImGui::SetNextItemWidth(100);
    ImGui::SliderFloat("fps delay: ", &Time::getFpsDelay(), 0.1, 1.f);

    ImGui::Checkbox("world delay enabled", &m_enabled_world_delay);
    if (m_enabled_world_delay)
    {
        ImGui::Text("delay: %f seconds", Time::getWorldDelay());
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("##world", &Time::getWorldDelay(), 1.f, 60.f);
    }
    // automatically invoke a reset
    if (m_enabled_world_delay && Time::worldTimerUpdate()) m_current_world->reset();


    ImGui::Checkbox("spawn delay enabled", &m_enabled_spawn_delay);
    if (m_enabled_spawn_delay)
    {
        ImGui::Text("delay: %f seconds", Time::getSpawnDelay());
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("##spawn", &Time::getSpawnDelay(), 0.025f, 1.f);
    }
    // automatically spawn an Entity
    if (m_enabled_spawn_delay && Time::spawnTimerUpdate() && !m_current_world->paused())
    {
        // spawn at mouse cursor. Can be modified!
        m_current_world->spawnEntity({ 0.f, 0.f });
    }

    ImGui::Text("speed: x%f", truncf(Time::scale));
    // just for fun lol
    if (ImGui::Button("x1"))    Time::scale = 1.f;
    if (ImGui::Button("x2"))    Time::scale = 2.f;
    if (ImGui::Button("x5"))    Time::scale = 5.f;

    ImGui::End();
}

