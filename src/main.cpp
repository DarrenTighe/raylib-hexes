#include <raylib-cpp.hpp>
#include "hexagonTransforms.hpp"
#include <string>

int main() {
    
    // Initialization
    int screenWidth = 1600;
    int screenHeight = 1200;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Experiment 2");
       
    Camera3D camera = { 0 };
    camera.position = Vector3{100.0f, 100.0f, 100.0f};
    camera.target = Vector3{0.0f, 0.0f, 0.0f};
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                               
    //camera.projection = CAMERA_PERSPECTIVE;  
    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);

    HexagonTransforms ht (5, pointytop_orientation);

    HexCoord highlightedhex = {0, 0};
    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update
        UpdateCamera(&camera);
        Ray ray = GetMouseRay(GetMousePosition(), camera);
        RayHitInfo groundhit = GetCollisionRayGround(ray, 0.0f);
        // TODO: Update your variables here
        
        if (groundhit.hit){
            highlightedhex = ht.getCoordForTransform(
                Vector2{groundhit.position.x, groundhit.position.z}
                );
        } else {
            highlightedhex = {0, 0};
        }


        std::string qstr = std::to_string(highlightedhex.q);
        std::string rstr = std::to_string(highlightedhex.r);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // origin marker

        DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 5.0f, 1.0f, GREEN);
        DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 5.0f, 1.0f, 1.0f, BLUE);
        DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 5.0f, RED);


        for (int q = -5; q<6; q++){
            for (int r = -5; r < 6; r++){
                raylib::Vector2 pos = ht.getHexTransform(q,r);
                Vector3 worldpos = Vector3{pos.GetX(), 0.0f, pos.GetY()};
                DrawCylinderWires(worldpos,5.0f, 5.0f, 1.0f, 6, RED);
            }
        }

        // Highlighted hex
        Vector2 highpos = ht.getHexTransform(highlightedhex.q, highlightedhex.r);
        DrawCylinder(Vector3{highpos.x, 0.0f, highpos.y},5.0f, 5.0f, 1.0f, 6, RED);
        EndMode3D();
        textColor.DrawText(("(q, r) = (" + qstr + ", " + rstr + ")" ).c_str(), 190, 200, 20);
        EndDrawing();
    }

    return 0;
}