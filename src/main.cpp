#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <string>

////////////////////////////////////////////////////////////
int main()
{

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Cmake with SFML with Dear IMGUI Demo!" };
    window.setFramerateLimit(144);
    ImGui::SFML::Init(window);

    // good to have - variables
    const double PI = 3.1415;
    bool dev_tools_active = true;

    float mainView_angle = 0;
    float bricks_angle   = 0;

    std::string log = "text here";
    sf::Clock clock;

    //SFML
    sf::Texture bricks_texture;
    sf::Sprite  bricks_sprite;

    //SFML Sprite set up
    if (!bricks_texture.loadFromFile("/home/seo/CLionProjects/physics_plane_test/bricks.jpg")) return EXIT_FAILURE;
    bricks_sprite.setTexture(bricks_texture);
    bricks_texture.setRepeated(true);

    bricks_sprite.setOrigin(bricks_texture.getSize().x / 2,
                            bricks_texture.getSize().y / 2);
    bricks_sprite.setPosition(window.getSize().x / 2,
                              window.getSize().y / 2);
    bricks_sprite.setRotation(0.f);


    //VIEWS
    sf::View mainView(window.getView());
             mainView.setCenter(mainView.getSize().x / 2,
                                mainView.getSize().y / 2);

    //VIEW TRANSFORM  (for dragging)
    sf::Vector2i prev_mouse_pos (0,0);


    while (window.isOpen())
    {

        ImGui::SFML::Update(window, clock.restart());

        //SFML VIEW LOGIC
        window.setView(mainView);
        mainView.setRotation(mainView_angle * 180 / PI);
        bricks_sprite.setRotation(bricks_angle * 180 / PI);

        // SFML-IMGUI EVENTS
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            //MOUSE
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))    log = "left click detected";
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))  log = "middle click detected";
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))   log = "right click detected";

            //if (event.mouseWheel.delta != 0)
            //{
            //    (event.mouseWheel.delta > 0) ? log = "scroll up detected": log = "scroll down detected";
            //}
            /*if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                //Drag the main view
                log = "left click dragged";
                mainView.move(prev_mouse_pos.x - sf::Mouse::getPosition(window).x,
                              prev_mouse_pos.y - sf::Mouse::getPosition(window).y);
                prev_mouse_pos = sf::Mouse::getPosition(window);
            }*/

        }


        ImGui::Begin("test window", NULL, ImGuiWindowFlags_AlwaysUseWindowPadding);
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::Button("Kinematics")) { log = "Kinematics clicked"; }
            if (ImGui::Button("Dynamics"  )) { log = "Dynamics clicked"; }
            if (ImGui::Button("Rotational")) { log = "Rotational clicked"; }

            ImGui::TextColored(ImVec4(244,488,30,255), "More");
            if (ImGui::Button("Dev-Tools"))  { dev_tools_active = !dev_tools_active; }

            ImGui::EndMainMenuBar();
        }
        ImGui::End();


        //Events
        if (dev_tools_active)
        {
            ImGui::Begin("Pre-Build Testing Window", &dev_tools_active, ImGuiWindowFlags_AlwaysUseWindowPadding);
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
            ImGui::Text(std::to_string(mainView_angle).c_str());

            ImGui::SliderAngle("Bricks Rotation", &bricks_angle);
            ImGui::Text("Bricks_Rotation");
            ImGui::Text(std::to_string(bricks_angle).c_str());

            ImGui::Text("Bricks_Origin");
            ImGui::Text(std::to_string(bricks_sprite.getOrigin().x).c_str());
            ImGui::Text(std::to_string(bricks_sprite.getOrigin().y).c_str());


            //display age
            ImGui::Text("Log INFO:");
            ImGui::Text(log.c_str());
            ImGui::End();
        }



        window.clear();
        //RENDER SFML
        window.draw(bricks_sprite);

        //RENDER IMGUI
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}