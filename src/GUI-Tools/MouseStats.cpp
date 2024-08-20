#include "GuiTools.hpp"

////////////////////////////////////////
////
////  Implementation for GuiTools.h
////
////////////////////////////////////////

void GuiTools::MouseStats()
{
    ImGui::Begin("Mouse Stats", &m_MouseStats_active, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SeparatorText("Mouse Info");

    ImGui::Text("x: %i    y: %i",
                sf::Mouse::getPosition(*m_window).x,
                sf::Mouse::getPosition(*m_window).y);

    // Output mouse pos relative to screen pixels
    ImGui::TextColored(sf::Color(211,122,56, 250), "In Screen Pixel Coords");
    const sf::Vector2i mouse_px = m_window->mapCoordsToPixel(
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window)));
    ImGui::Text("x: %i    y: %i",
                mouse_px.x,
                mouse_px.y);
    ImGui::SeparatorText("Select Rectangle Info");

    ImGui::Text("pos x: %i  y: %i",
                DragHandler::getDraggedRectangle().getPosition().x,
                DragHandler::getDraggedRectangle().getPosition().y);

    ImGui::Text("size x: %f  y: %f",
                DragHandler::getDraggedRectangle().getSize().x,
                DragHandler::getDraggedRectangle().getSize().y);

    ImGui::SeparatorText("Dragging Info");
    ImGui::Text("%s and %s", DragHandler::isDragging() ? "Mouse dragging":"Mouse NOT dragging",
                DragHandler::isSelecting() ? "currently selecting": "NOT selecting");
    ImGui::Text("Delta pos x: %i  y: %i",
                DragHandler::getDeltaPos().x,
                DragHandler::getDeltaPos().y);

    ImGui::Text("Delta pos total  x: %i  y: %i",
                DragHandler::getDeltaTotalPos().x,
                DragHandler::getDeltaTotalPos().y);
    ImGui::End();
}


