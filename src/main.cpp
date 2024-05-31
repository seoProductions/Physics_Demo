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
    bool dev_tools_active = false;
    std::string log = "text here";
    sf::Clock clock;


    //SFML
    sf::Texture bricks_texture;
    sf::Sprite  bricks_sprite;

    bricks_sprite.setPosition(window.getSize().x / 2,
                              window.getSize().y / 2);
    bricks_sprite.setRotation(0.f);

    //VIEWS
    float mainView_angle = 0;
    sf::View mainView(window.getView());
             mainView.setCenter(mainView.getSize().x / 2,
                                mainView.getSize().y / 2);
             mainView.setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.25f));


    //SFML Sprite actions
    if (!bricks_texture.loadFromFile("/home/seo/CLionProjects/physics_plane_test/bricks.jpg")) return EXIT_FAILURE;
    bricks_sprite.setTexture(bricks_texture);
    bricks_texture.setRepeated(true);

    while (window.isOpen())
    {

        //Events
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        ImGui::SFML::Update(window, clock.restart());


        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::Button("Kinematics")) { log = "Kinematics clicked"; }
            if (ImGui::Button("Dynamics"  )) { log = "Dynamics clicked"; }
            if (ImGui::Button("Rotational")) { log = "Rotational clicked"; }

            ImGui::TextColored(ImVec4(244,488,30,255), "More");
            if (ImGui::Button("Dev-Tools"))  { dev_tools_active = !dev_tools_active; }


            ImGui::EndMainMenuBar();
        }

        if (dev_tools_active)
        {
            ImGui::Begin("Main Window", &dev_tools_active, ImGuiWindowFlags_AlwaysAutoResize);
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
            ImGui::SliderAngle("View Rotation", &mainView_angle);
            ImGui::Text("Main_View_Rotation");
            ImGui::Text(std::to_string(mainView_angle).c_str());

            //display age
            ImGui::Text("Log INFO:");
            ImGui::Text(log.c_str());
            ImGui::End();
        }



        //SFML VIEW LOGIC
        window.setView(mainView);
        mainView.setRotation(mainView_angle * 180 / PI);


        window.clear();
        //RENDER SFML
        window.draw(bricks_sprite);

        //RENDER IMGUI
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}