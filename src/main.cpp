#include "WorldSpace.hpp"
#include "DragHandler.hpp"
#include "GridSpace.hpp"
#include "GUI-Tools/GuiTools.hpp"
#include "Time.hpp"

#include "ImGuiStyle.hpp"


////////////////////////////////////////////////////////////
int main()
{
    // Set up SFML window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Cmake with SFML with Dear IMGUI Demo!", sf::Style::Default, settings };
    window.setFramerateLimit(144);

    // Combine with Im-Gui
    if (!ImGui::SFML::Init(window)) return EXIT_FAILURE;

    // DRAGHANDLER & EVENT
    sf::Event event {};
    DragHandler::init(&window, &event);

    //VIEWS

    //INIT World Space List
    std::array<WorldSpace, 4> WorldSpaceList =
            {
                WorldSpace("Vectors & 2D Kinematics"),
                WorldSpace("Forces & RigidBodies"),
                WorldSpace("Torque & Rotation"),
                WorldSpace("Sandbox FFA")
            };

    // Demo will start on World 0
    WorldSpace &current_world = WorldSpaceList[0];
    current_world.Activate();

    // !!!DONT FORGET TO INIT!!!
    WorldSpace::initBehavior(WorldSpaceList);   // pass reference

    // GUI TOOLS
    GuiTools::init(&window, &current_world, WorldSpaceList);

    style();

    // GRID SPACE
    GridSpace::init(&current_world, &window);
    GridSpace::updateGrid();

    // Set-up World 0
    current_world.start();

    while (window.isOpen())
    {
        //TIME
        Time::updateDeltaTime();

        // SFML VIEW LOGIC
        window.setView(current_world.m_worldview);

        // Keep IMGUI in sync
        ImGui::SFML::Update(window, Time::getSFMLTime());

        // SFML-IMGUI EVENTS
        for (; window.pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(window, event);

            // WINDOW CLOSE
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // PAUSING
            if (ImGui::IsKeyPressed(ImGuiKey_Space)) current_world.TogglePause();

            // HANDLE DRAGGING on condition
            if (!ImGui::GetIO().WantCaptureMouse)   // FIXME: drags continue when hovering ImGui:: Window
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
                // messy world view translation :o TODO looking for fix - deltaPos bugs - UNSTABLE at LARGE COORDS
                current_world.m_worldview.move(DragHandler::getDeltaPosLocal());

                // Update when current view changes
                GridSpace::updateGrid();
            }

        }

        const float VIEW_SPEED = 500.f;   // scale factor
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            current_world.m_worldview.move({ current_world.m_worldview.getSize().x / VIEW_SPEED, 0.f });
            // Update when current view changes
            GridSpace::updateGrid();
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            current_world.m_worldview.move({ -current_world.m_worldview.getSize().x / VIEW_SPEED, 0.f });
            // Update when current view changes
            GridSpace::updateGrid();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            current_world.m_worldview.move({ 0.f, -current_world.m_worldview.getSize().y / VIEW_SPEED });
            // Update when current view changes
            GridSpace::updateGrid();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            current_world.m_worldview.move({ 0.f, current_world.m_worldview.getSize().y / VIEW_SPEED });
            // Update when current view changes
            GridSpace::updateGrid();
        }

        //// Dont Forget To update
        //// Dont Forget To update
        //// Dont Forget To update

        // call to UNIQUE world update() on condition
        if (!current_world.paused())
            current_world.update();

        // Update GUI
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

        // RENDER GRIDSPACE TEXT
        // on default view - preserves SFML text scaling
        window.setView(window.getDefaultView());
        for (const auto& text : GridSpace::getGridLinesText())
            window.draw(text);

        //RENDER IMGUI
        ImGui::SFML::Render(window);
        window.display();
    }


    ImGui::SFML::Shutdown();
    return EXIT_SUCCESS;
}