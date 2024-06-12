#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <string>
#include <algorithm>

#include "WorldSpace.h"
#include "DragHandler.h"

////////////////////////////////////////////////////////////
int main()
{

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Cmake with SFML with Dear IMGUI Demo!" };
    window.setFramerateLimit(144);
    if (!ImGui::SFML::Init(window)) return EXIT_FAILURE;

    // DRAGHANDLER & EVENT
    sf::Event event;
    DragHandler::init(&window, &event);


    // good to have - variables
    bool dev_tools_active = true;
    float mainView_angle = 0;

    // temporary variables
    float bricks_angle   = 0;

    std::string log = "log text here!";


    //VIEWS
    sf::View mainView(window.getView());
             mainView.setCenter(mainView.getSize().x / 2,
                                mainView.getSize().y / 2);

    //VIEW TRANSFORM  (for dragging)
    sf::Vector2f prev_mouse_pos (0,0);

    //INIT World Space List
    std::array<WorldSpace, 3> WorldSpaceList =
            {
                WorldSpace("Kinematics"),
                WorldSpace("Dynamics"),
                WorldSpace("Rotation"),
                // more comming soon
            };

    // DEFAULT
    WorldSpace current_world = WorldSpaceList[0];   //std::array return reference

    ////
    ////      TEMPORARY
    ////SFML
    sf::Texture bricks_texture;

    //SFML Sprite set up
    if (!bricks_texture.loadFromFile("/home/seo/CLionProjects/physics_plane_test/bricks.jpg")) return EXIT_FAILURE;
    WorldSpaceList[0].m_shape.setTexture(&bricks_texture);
    WorldSpaceList[0].m_shape.setSize(sf::Vector2f (433,233));
    WorldSpaceList[0].m_shape.setOrigin(bricks_texture.getSize().x / 2,
                                         bricks_texture.getSize().y / 2);
    WorldSpaceList[0].m_shape.setPosition(window.getSize().x / 2,
                                           window.getSize().y / 2);
    WorldSpaceList[0].m_shape.setRotation(0.f);

    WorldSpaceList[1].m_shape = sf::RectangleShape(sf::Vector2f (299, 150));

    sf::Clock clock;
    while (window.isOpen())
    {

        //SFML VIEW LOGIC
        window.setView(current_world.m_worldview);
        current_world.m_worldview.setRotation(mainView_angle * 180 / 3.1415);
        current_world.m_shape.setRotation   (bricks_angle * 180 / 3.1415);

        ImGui::SFML::Update(window, clock.restart());

        // SFML-IMGUI EVENTS
        for (event; window.pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            //MOUSE CLICKS
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))    log = "left click detected";
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))   log = "right click detected";
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))  log = "middle click detected";

            // HANDLE DRAGGING
            DragHandler::updateDragging();

            //MOUSE SCROLLING
            //Credit to: https://github.com/SFML/SFML/wiki/Source:-Zoom-View-At-%28specified-pixel%29
            if (event.type == sf::Event::MouseWheelScrolled)
            {   log = "mouse is scrolling";
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
        }

        ImGui::Begin("INFO window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::Button("Kinematics"))
            {   log = "Kinematics clicked";

                current_world.m_isActive = false;
                current_world = WorldSpaceList[0];
                current_world.m_isActive = true;
            }

            if (ImGui::Button("Dynamics"))
            {   log = "Dynamics clicked";

                current_world.m_isActive = false;
                current_world = WorldSpaceList[1];
                current_world.m_isActive = true;
            }

            if (ImGui::Button("Rotational"))
            {   log = "Rotational clicked";

                current_world.m_isActive = false;
                current_world = WorldSpaceList[2];
                current_world.m_isActive = true;
            }

            ImGui::TextColored(sf::Color(211,122,56, 250), "More");
            if (ImGui::Button("Dev-Tools"))  { dev_tools_active = !dev_tools_active; }

            ImGui::EndMainMenuBar();
        }

        // Output mouse pos relative to *window
        ImGui::Text("Mouse x: %i    Mouse y: %i",
                sf::Mouse::getPosition(window).x,
                sf::Mouse::getPosition(window).y);

        // Output mouse pos relative to screen pixels
        ImGui::TextColored(sf::Color(211,122,56, 250), "In Screen Pixel Coords");
        const sf::Vector2i mouse_px = window.mapCoordsToPixel(
                static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        ImGui::Text("Mouse x: %i    Mouse y: %i",
                    mouse_px.x,
                    mouse_px.y);

        // Output view pos relative to *window
        ImGui::Text("Current View centered at x: %i  y: %i",
                            current_world.m_worldview.getCenter().x,
                            current_world.m_worldview.getCenter().y);

        ImGui::Text("DraggableRectangle pos x: %i  y: %i",
                    DragHandler::getDraggedRectangle().getPosition().x,
                    DragHandler::getDraggedRectangle().getPosition().y);

        ImGui::Text("size x: %i  y: %i",
                    DragHandler::getDraggedRectangle().getSize().x,
                    DragHandler::getDraggedRectangle().getSize().y);

        ImGui::Text("Delta pos x: %i  y: %i",
                    DragHandler::getDeltaPos().x,
                    DragHandler::getDeltaPos().y);
        ImGui::Text("Delta pos total  x: %i  y: %i",
                    DragHandler::getDeltaTotalPos().x,
                    DragHandler::getDeltaTotalPos().y);

        ImGui::End();

        //Events
        if (dev_tools_active)
        {
            ImGui::Begin("Pre-Build Testing Window", &dev_tools_active, ImGuiWindowFlags_AlwaysAutoResize);
            //menu
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("ShortCuts"))
                {
                    if (ImGui::MenuItem("Deactivate", "Ctrl+W")) { dev_tools_active = false; }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            //DEBUG
            ImGui::SliderAngle("View Rotation", &mainView_angle);
            ImGui::Text("Main_View_Rotation");
            ImGui::Text("%f", mainView_angle);

            ImGui::SliderAngle("Bricks Rotation", &bricks_angle);
            ImGui::Text("Bricks_Rotation");
            ImGui::Text("%f", bricks_angle);


            ImGui::Text("Current World is:");
            ImGui::Text("%s", current_world.m_name.c_str());

            //display age
            ImGui::Text("Log INFO:");
            ImGui::Text("%s", log.c_str());
            ImGui::End();
        }



        window.clear();
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