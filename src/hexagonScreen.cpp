# include "hexagonScreen.hpp"

HexagonScreen::HexagonScreen(){
    camera.position = Vector3{100.0f, 100.0f, 100.0f};
    camera.target = Vector3{0.0f, 0.0f, 0.0f};
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;     
    SetCameraMode(camera, CAMERA_FREE);
}

void HexagonScreen::update(){
    UpdateCamera(&camera);
    Ray ray = GetMouseRay(GetMousePosition(), camera);
    RayHitInfo groundhit = GetCollisionRayGround(ray, 0.0f);


    if (groundhit.hit){
        highlightedHex = ht.getCoordForTransform(
            Vector2{groundhit.position.x, groundhit.position.z}
        );
    } else {
        highlightedHex = {0, 0};
    }

    qstr = std::to_string(highlightedHex.q);
    rstr = std::to_string(highlightedHex.r);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    // origin marker
    DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 5.0f, 1.0f, GREEN);
    DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 5.0f, 1.0f, 1.0f, BLUE);
    DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 5.0f, RED);
    
    //hexes
    for (int q = -5; q<6; q++){
            for (int r = -5; r < 6; r++){
                raylib::Vector2 pos = ht.getHexTransform(q,r);
                Vector3 worldpos = Vector3{pos.GetX(), 0.0f, pos.GetY()};
                DrawCylinderWires(worldpos,5.0f, 5.0f, 1.0f, 6, RED);
            }
        }

    // Highlighted hex
    Vector2 highpos = ht.getHexTransform(highlightedHex.q, highlightedHex.r);
    DrawCylinder(Vector3{highpos.x, 0.0f, highpos.y},5.0f, 5.0f, 1.0f, 6, RED);

    EndMode3D();
    textColor.DrawText(("(q, r) = (" + qstr + ", " + rstr + ")" ).c_str(), 190, 200, 20);
    EndDrawing();
};