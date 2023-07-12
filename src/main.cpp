#include <cstdlib>
#include <iostream>

#include "raylib.h"
#include "GameWorld.h"

#include "config.h"



int main() {
    using namespace std;
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file


    InitWindow(1024*3/2,512,"The thingy");
    SetTargetFPS(60);
    bool doSlowGen;

    while (IsKeyUp(KEY_ENTER)){
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
    SetRandomSeed(time(nullptr));
    GameWorld* theWorld = new GameWorld(GetRandomValue(0, 1024*32),GetScreenWidth(),GetScreenHeight());
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

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here

        if (IsKeyPressed(KEY_G)){
            theWorld->setSeed(theWorld->getSeed()+16);
            theWorld->genWorld(false);
        }

        BeginDrawing();
            // You can draw on the screen between BeginDrawing() and EndDrawing()
            // ...
            // ...
            theWorld->draw(false);
            ClearBackground(WHITE);
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
