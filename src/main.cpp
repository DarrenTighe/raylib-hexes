#include <raylib-cpp.hpp>
#include "hexagonTransforms.hpp"
#include <string>
#include "gamescreen.hpp"
#include "hexagonscreen.hpp"

int main() {
    
    // Initialization
    int screenWidth = 1600;
    int screenHeight = 1200;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Experiment 2");
       
    SetTargetFPS(60);

    HexagonScreen currentscreen = HexagonScreen();

    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        currentscreen.update();
    }

    return 0;
}