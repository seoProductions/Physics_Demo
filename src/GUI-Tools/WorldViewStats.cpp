#include "GuiTools.h"

////////////////////////////////////////
////
////  Implementation for GuiTools.h
////
////////////////////////////////////////

void GuiTools::ViewStats()
{
    ImGui::Begin("World View Stats", &m_ViewStats_active, ImGuiWindowFlags_AlwaysAutoResize);

    // helper variable
    const sf::View& view = m_current_world->m_worldview;

    ImGui::SeparatorText("SFML View");
    ImGui::Text("Centered at x: %f y: %f",view.getCenter().x,
                                        view.getCenter().y);
    ImGui::Text("size x: %f y: %f",   view.getSize().x,
                                    view.getSize().y);
    ImGui::Text("rotation: %f", view.getRotation());

    ImGui::SeparatorText("SFML View PORT");
    ImGui::Text("Located at x: %f y: %f",   view.getViewport().getPosition().x,
                                            view.getViewport().getPosition().y);
    ImGui::Text("port size x: %f y: %f",    view.getViewport().getSize().x,
                                            view.getViewport().getSize().y);
    ImGui::End();
}
