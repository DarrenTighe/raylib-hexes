
#include "hexagonTransforms.hpp"


HexagonTransforms::HexagonTransforms(int hexsize, HexOrientation orient){
        hexagonsize = hexsize;
        orientation = orient;
};

raylib::Vector2 HexagonTransforms::getHexTransform(int q, int r){

    float x;
    float y;
    if (orientation == flattop_orientation){
        x = hexagonsize * 3.0/2 * q;
        y = hexagonsize * (sqrtf(3.0)/2 * q + sqrtf(3)*r);
    }else {
        y = hexagonsize * 3.0/2 * q;
        x = hexagonsize * (sqrtf(3.0)/2 * q + sqrtf(3)*r);
    }
    return raylib::Vector2(x, y);
}

raylib::Vector2 HexagonTransforms::getHexTransform(HexCoord coord){
    return getHexTransform(coord.q, coord.r);
}

HexCoord HexagonTransforms::getCoordForTransform(raylib::Vector2 transform){
    float q;
    float r;

    if(orientation == flattop_orientation){
        q = (sqrtf(3)/3 * transform.GetY() - 1.0/3 * transform.GetX()) / hexagonsize;
        r = (2.0/3 * transform.GetY()) / hexagonsize;
    }else{
        r = (sqrtf(3)/3 * transform.GetX() - 1.0/3 * transform.GetY()) / hexagonsize;
        q = (2.0/3 * transform.GetY()) / hexagonsize;
    }
    return hexRound(raylib::Vector2(q, r));
}

HexCoord HexagonTransforms::hexRound(raylib::Vector2 coord_v){
    float x = coord_v.GetX();
    float y = coord_v.GetY();
    float z = -x -y;

    float rx = roundf(x);
    float ry = roundf(y);
    float rz = roundf(z);

    float x_diff = abs(rx - x);
    float y_diff = abs(ry - y);
    float z_diff = abs(rz - z);

    if (x_diff > y_diff && x_diff > z_diff){
        rx = -ry - rz;
    }  else if (y_diff > z_diff) {
        ry = -rx -rz;
    } else {
        rz = -rx-ry;
    }
    return {(int)round(rx), (int)round(ry)};
}

