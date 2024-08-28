#cmake project with imgui-sfml repo
#https://github.com/SFML/cmake-sfml-project/tree/imgui-sfml

cmake_minimum_required(VERSION 3.16)
project(Physics_Demo LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
#
include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

add_executable(Physics_Demo src/main.cpp
        src/DragHandler.hpp
        src/DragHandler.cpp
        src/WorldSpace.hpp
        src/WorldSpace.cpp
        src/GridSpace.hpp
        src/GridSpace.cpp
        src/GUI-Tools/GuiTools.hpp
        src/GUI-Tools/GuiTools.cpp
        src/GUI-Tools/MouseStats.cpp
        src/GUI-Tools/WorldViewStats.cpp
        src/GUI-Tools/GridStats.cpp
        src/Entity/Entity.hpp
        src/Entity/RigidBody.hpp
        src/Entity/RigidBody.cpp
        src/GUI-Tools/TimeStats.cpp
        src/Random/random.hpp
        src/Entity/KinematicBody.cpp
        src/Entity/KinematicBody.hpp
        src/Entity/Body.hpp
        src/Camera.cpp
        src/Camera.hpp
        src/ArrowShape.cpp
        src/ArrowShape.hpp)


target_link_libraries(Physics_Demo     PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)
target_compile_features(Physics_Demo PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET Physics_Demo
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Physics_Demo>
            VERBATIM)
endif()

install(TARGETS Physics_Demo)