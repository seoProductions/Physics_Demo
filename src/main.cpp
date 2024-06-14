#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <algorithm>

#include "WorldSpace.h"
#include "DragHandler.h"
#include "GUI-Tools/GuiTools.h"


////////////////////////////////////////////////////////////
int main()
{

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Cmake with SFML with Dear IMGUI Demo!" };
    window.setFramerateLimit(144);
    if (!ImGui::SFML::Init(window)) return EXIT_FAILURE;

    // DRAGHANDLER & EVENT
    sf::Event event {};
    DragHandler::init(&window, &event);



    //VIEWS
    sf::View mainView(window.getView());
             mainView.setCenter(mainView.getSize().x / 2,
                                mainView.getSize().y / 2);  // middle


    //INIT World Space List
    std::array<WorldSpace, 3> WorldSpaceList =
            {
                WorldSpace("Kinematics"),
                WorldSpace("Dynamics"),
                WorldSpace("Rotation"),
                // more coming soon
            };

    // DEFAULT
    WorldSpace current_world = WorldSpaceList[0];   //std::array return reference
    current_world.m_isActive = true;    // activate

    // GUI TOOLS
    GuiTools::init(&window, &current_world);

    // GRID SPACE
    GridSpace::init(&current_world);

    sf::Clock clock;
    while (window.isOpen())
    {

        //SFML VIEW LOGIC
        window.setView(current_world.m_worldview);
        ImGui::SFML::Update(window, clock.restart());

        // SFML-IMGUI EVENTS
        for (; window.pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // HANDLE DRAGGING
            DragHandler::updateDragging();

            //MOUSE SCROLLING
            //Credit to: https://github.com/SFML/SFML/wiki/Source:-Zoom-View-At-%28specified-pixel%29
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                float zoom = (event.mouseWheelScroll.delta < 0) ? 1.1: 0.9;

                const sf::Vector2f beforeCoord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::View& view = current_world.m_worldview;     // reference
                view.zoom(zoom);
                window.setView(view);
                const sf::Vector2f afterCoord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
                view.move(offsetCoords);
                window.setView(view);

            }

            // Drag the view on Middle-Click Drag
            if (DragHandler::isDragging() && !DragHandler::isSelecting())
            {
                // messy world view translation :o
                current_world.m_worldview.move(-static_cast<sf::Vector2f>(window.mapCoordsToPixel(
                        window.mapPixelToCoords(DragHandler::getDeltaPos()))));        // translate to pixel coords
            }

            // Dont forget to update
            GridSpace::updateGrid();
        }

        ////////////////////////////////
        ////
        //// Main Menu Bar using ImGui
        ////
        ////////////////////////////////

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::Button("Kinematics"))
            {
                current_world.m_isActive = false;
                current_world = WorldSpaceList[0];
                current_world.m_isActive = true;
            }

            if (ImGui::Button("Dynamics"))
            {

                current_world.m_isActive = false;
                current_world = WorldSpaceList[1];
                current_world.m_isActive = true;
            }

            if (ImGui::Button("Rotational"))
            {

                current_world.m_isActive = false;
                current_world = WorldSpaceList[2];
                current_world.m_isActive = true;
            }

            ImGui::TextColored(sf::Color(211,122,56, 250), "More");

            if (ImGui::Button("Properties")) { GuiTools::m_Properties_active = !GuiTools::m_Properties_active; }
            if (ImGui::Button("Dev-Tools"))  { GuiTools::m_DevTools_active = !GuiTools::m_DevTools_active; }
            if (ImGui::Button("Settings"))   { GuiTools::m_Settings_active = !GuiTools::m_Settings_active; }

            ImGui::EndMainMenuBar();

            //// Dont Forget to update
            GuiTools::updateGUI();
        }

        ////////////////
        ////
        //// Rendering
        ////
        ////////////////

        window.clear();
        //RENDER GRIDSPACE
        for (const auto& lines: GridSpace::getGridLines())
            window.draw(lines);

        //RENDER SFML
        window.draw(current_world.m_shape);

        //RENDER DRAGGED RECTANGLE - on condition
        if (DragHandler::isSelecting())
            window.draw(DragHandler::getDraggedRectangle());


        //RENDER IMGUI
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return EXIT_SUCCESS;
}