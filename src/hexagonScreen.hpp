#pragma once
#include "gameScreen.hpp"
#include <raylib-cpp.hpp>
#include "hexagonTransforms.hpp"

class HexagonScreen: public GameScreen {
    public:
        HexagonScreen();
        void update() override;
    private:
        Camera3D camera = {0}; 
        HexagonTransforms ht = HexagonTransforms(5, pointytop_orientation);
        HexCoord highlightedHex = {0, 0};
        std::string qstr;
        std::string rstr;
        raylib::Color textColor = LIGHTGRAY;
};