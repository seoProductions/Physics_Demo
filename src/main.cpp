#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <algorithm>

#include "WorldSpace.h"
#include "DragHandler.h"
#include "GridSpace.h"
#include "GUI-Tools/GuiTools.h"

#include "ImGuiStyle.h"

////////////////////////////////////////////////////////////
int main()
{
    // Set up SFML window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Cmake with SFML with Dear IMGUI Demo!", sf::Style::Default, settings };
    window.setFramerateLimit(144);

    // Combine with Im-Gui
    if (!ImGui::SFML::Init(window)) return EXIT_FAILURE;

    // DRAGHANDLER & EVENT
    sf::Event event {};
    DragHandler::init(&window, &event);

    //VIEWS
    sf::View mainView(window.getView());
             mainView.setCenter(mainView.getSize().x / 2,
                                mainView.getSize().y / 2);  // middle

    //INIT World Space List
    std::vector<WorldSpace> WorldSpaceList =
            {
                WorldSpace("Motion"),
                WorldSpace("Forces"),
                WorldSpace("Rotation"),
            };

    // DEFAULT
    WorldSpace current_world = WorldSpaceList[0];   //std::array return reference
    current_world.m_isActive = true;    // activate

    // GUI TOOLS
    GuiTools::init(&window, &current_world, WorldSpaceList);

    style();

    // GRID SPACE
    GridSpace::init(&current_world);
    GridSpace::updateGrid();

    sf::Clock clock;
    while (window.isOpen())
    {

        // SFML VIEW LOGIC
        window.setView(current_world.m_worldview);

        // Keep IMGUI in sync
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
                float zoom = (event.mouseWheelScroll.delta < 0) ? 1.05: 0.95;

                const sf::Vector2f beforeCoord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::View& view = current_world.m_worldview;     // reference
                view.zoom(zoom);
                window.setView(view);
                const sf::Vector2f afterCoord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
                view.move(offsetCoords);
                window.setView(view);

                // Update when current view changes
                GridSpace::updateGrid();
            }

            // Drag the view on Middle-Click Drag
            if (DragHandler::isDragging() && !DragHandler::isSelecting())
            {
                // messy world view translation :o
                current_world.m_worldview.move(-static_cast<sf::Vector2f>(window.mapCoordsToPixel(
                        window.mapPixelToCoords(DragHandler::getDeltaPos()))));        // translate to pixel coords

                // Update when current view changes
                GridSpace::updateGrid();
            }
        }


        //// Dont Forget To update
        GuiTools::updateGUI();

        ////////////////
        ////
        //// Rendering
        ////
        ////////////////

        window.clear();

        //RENDER GRIDSPACE
        for (const auto& lines: GridSpace::getGridLines())
            window.draw(lines);

        //RENDER SFML ENTITY ( shapes )
        for (const auto& entity: current_world.m_entity_list)
        {
            window.draw(*entity.m_shape);
        }

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