#include <cstdlib>
#include <iostream>

#include "raylib.h"
#include "GameWorld.h"

#include "config.h"
#include "math.h"


int main() {
    using namespace std;
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file


    InitWindow(1024*3/2,512,"The thingy");
    SetTargetFPS(60);
    bool doSlowGen;

    while (IsKeyUp(KEY_ENTER) && !WindowShouldClose()){
        if (IsKeyPressed(KEY_Y)){
            doSlowGen = true;
        }
        if (IsKeyPressed(KEY_N)){
            doSlowGen = false;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("DO SLOW GEN?\n Y/N", 10, 10, 10, WHITE);
        DrawRectangle(10,40,40,40,doSlowGen?GREEN:RED);
        EndDrawing();
    }
    SetRandomSeed(GetRandomValue(0,pow(2,20)));
    GameWorld* theWorld = new GameWorld(0,GetScreenWidth(),GetScreenHeight());
    SetTargetFPS(0);
    theWorld->genWorld(doSlowGen);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...
    Texture2D myTexture = LoadTexture("assets/graphics/testimage.png");
    Camera2D mainCam = {{},{},0,1};
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here

        if (IsKeyPressed(KEY_G)){
            theWorld->setSeed(theWorld->getSeed()+16);
            theWorld->genWorld(false);
        }
        if (IsKeyPressed(KEY_P)){
            mainCam.zoom += 0.25;
        }
        if (IsKeyPressed(KEY_M)){
            mainCam.zoom -= 0.25;
        }
        if (IsKeyDown(KEY_LEFT)){
            mainCam.target.x--;
        }
        if (IsKeyDown(KEY_RIGHT)){
            mainCam.target.x++;
        }
        if (IsKeyDown(KEY_UP)){
            mainCam.target.y--;
        }
        if (IsKeyDown(KEY_DOWN)){
            mainCam.target.y++;
        }

        BeginDrawing();
        BeginMode2D(mainCam);
        ClearBackground(WHITE);
        theWorld->draw(false);
        EndMode2D();
        DrawText(TextFormat("%i",GetFPS()), 10, 10, 30, LIGHTGRAY);

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...
    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
