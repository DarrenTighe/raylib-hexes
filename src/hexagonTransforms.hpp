#pragma once
#include <raylib-cpp.hpp>

enum HexOrientation{
    flattop_orientation, pointytop_orientation
};

struct HexCoord{
    int q;
    int r;
};

class HexagonTransforms{

    int hexagonsize; 
    HexOrientation orientation;

    public:
        HexagonTransforms(int hexsize, HexOrientation orient);
        raylib::Vector2 getHexTransform(int q, int r);
        raylib::Vector2 getHexTransform(HexCoord coord);
        HexCoord getCoordForTransform(raylib::Vector2 transform);
        HexCoord hexRound(raylib::Vector2 coord_v);

};