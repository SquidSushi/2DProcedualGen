//
// Created by mrbau on 11.07.2023.
//

#include "GameWorld.h"

GameWorld::GameWorld(int seed, int width, int height) {
    this->width = width;
    this->height = height;
    this->heightMap = GenImagePerlinNoise(width,1,seed,0,4);
    data = new block[width*height];
    for (int i = 0; i < width * height; i++){
        data[i] = block_air;
    }
    GenInitialSurface();
    FillUnderGround();
    FillOcean();

    genOutputTexture();
}

void GameWorld::GenInitialSurface() {
    for (int x = 0; x < width; x++){
        setBlock(x, 32 + 64 * GetImageColor(heightMap, x, 0).r / 256, block_stone);
    }
}

void GameWorld::draw(bool fullFrame) {
    if (fullFrame)BeginDrawing();

    DrawTextureEx(outputTexture.texture, {}, 0, (GetScreenWidth()/width), WHITE);

    if(fullFrame)EndDrawing();
}

void GameWorld::setBlock(int x, int y, block value) {
    x %= width; y %= height;
    data[x + (y * width)] = value;
}

block GameWorld::getBlock(int x, int y) {
    x %= width; y %= height;
    return data[x + y  * width];
}

void GameWorld::genOutputTexture() {
    Color blockColors[4] = {GetColor(0), GRAY, BROWN, BLUE};
    if (IsTextureReady(outputTexture.texture))
        UnloadRenderTexture(outputTexture);
    outputTexture = LoadRenderTexture(width,height);
    BeginTextureMode(outputTexture);
    ClearBackground(WHITE);
    DrawRectangleGradientV(0,0,width,height,BLACK,SKYBLUE);
    for (int y = 0; y < height; y++){
        for (int x = 0; x< width; x++){
            DrawPixel(x,y,blockColors[getBlock(x,y)]);
        }
    }
    EndTextureMode();
}

void GameWorld::FillUnderGround() {
    for (int x = 0; x < width; x++){
        bool columnStarted = false;
        for (int y = height; y>0; y--){
            if (columnStarted){
                setBlock(x, y-1, block_stone);
            }
            if (getBlock(x,y-1) == block_stone){
                columnStarted = true;
            }
        }
    }
}

void GameWorld::FillOcean() {
    for (int y = 0; y< 64; y++){
        for (int x = 0; x <  width; x++){
            if (getBlock(x,y) == block_air){
                setBlock(x,y,block_water);
            }
        }
    }
}
