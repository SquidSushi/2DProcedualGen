//
// Created by mrbau on 11.07.2023.
//

#include <cmath>
#include "GameWorld.h"

GameWorld::GameWorld(int seed, int width, int height) {
    this->width = width;
    this->height = height;
    //genHeightmap();
    data = new block[width*height];
    //genWorld(false);
    clearWorld(block_air);

    //genOutputTexture();
}

void GameWorld::genHeightmap() {
    if (IsImageReady(heightMap)){
        UnloadImage(heightMap);
    }
    heightMap = GenImagePerlinNoise(width, 1, seed, 0, 4);
}

void GameWorld::clearWorld(block with) {
    for (int i = 0; i < width * height; i++){
        data[i] = block_air;
    }
}

void GameWorld::genWorld(bool producePictures) {
    genHeightmap();
    clearWorld(block_air);
    GenInitialSurface(producePictures);
    FillOcean(producePictures);
    growDirt(producePictures);
    genOutputTexture();
}

void GameWorld::GenInitialSurface(bool producePictures) {
    for (int x = 0; x < width; x++){
        int columnHeight = groundBase + (groundVariance * GetImageColor(heightMap,x,0).r)/256;
        for (int y = 0; y < columnHeight; y++){
            setBlock(x,y,block_stone);
        }
        if (producePictures){
            drawCheap();
        }
    }
}

void GameWorld::draw(bool fullFrame) {
    if (fullFrame)BeginDrawing();

    DrawTextureEx(outputTexture.texture, {}, 0, (GetScreenWidth()/width), WHITE);

    if (IsKeyDown(KEY_L)){
        for (int column = 0; column < width/16;column++){
            DrawLine(column*16,0,column*16,height,BLACK);
        }
        for (int row = 0; row < height/16; row++){
            DrawLine(0,row * 16, width, row*16,BLACK);
        }
    }
    //DrawText(TextFormat("%i FPS", GetFPS()),10,10,20,BLACK);

    if(fullFrame)EndDrawing();
}
 void GameWorld::drawCheap() {
    if (cheapDrawCycle % 4 == 0){
    BeginDrawing();
     ClearBackground(BLACK);
    for (int y = 0; y< height; y++){
        for (int x = 0; x < width; x++){
            if (getBlock(x,y)>block_air)
            DrawRectangle(x,height-y,1,1,blockColors[getBlock(x,y)]);
        }
    }
     DrawFPS(0,0);
    EndDrawing();
    }
    cheapDrawCycle++;
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

    if (!IsRenderTextureReady(outputTexture)){
        outputTexture = LoadRenderTexture(width,height);
    }
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



void GameWorld::FillOcean(bool producePictures) {
    for (int y = 0; y< waterLevel; y++){
        for (int x = 0; x <  width; x++){
            if (getBlock(x,y) == block_air){
                setBlock(x,y,block_water);
            }
        }
        if (producePictures){
            drawCheap();
        }
    }
}

int GameWorld::getSeed() {
    return seed;
}

void GameWorld::setSeed(int val) {
    this->seed = val;
}

void GameWorld::growDirt(bool producePictures) {
    for (int x = 0; x < width; x++){
        int remainingColumnDirt = int(4 + float(1.5 * sin(x + seed/16.0) ));
        for (int y = height-1; y >= 0; y--){
            block currentBlock = getBlock(x,y);
            if (currentBlock == block_water)break;
            if (currentBlock != block_air && remainingColumnDirt > 0){
                setBlock(x,y,block_dirt);
                remainingColumnDirt--;
            }
            if (remainingColumnDirt <= 0) break;
        }
        if (producePictures)drawCheap();
    }
}
