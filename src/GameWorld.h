//
// Created by mrbau on 11.07.2023.
//
#pragma once

#include <vector>
#include "raylib.h"

#ifndef INC_2DPROCEDUALGEN_GAMEWORLD_H
#define INC_2DPROCEDUALGEN_GAMEWORLD_H

enum block{
    block_air = 0,
    block_stone,
    block_dirt,
    block_water,
};

class GameWorld {
    block* data;
    int width = 1;
    int height = 1;
    int seed = 0;
    int groundBase = 16;
    int groundVariance = 112;
    int waterLevel = 64;
    Image heightMap;
    RenderTexture heightMapTex;
    RenderTexture outputTexture;
    void setBlock(int x, int y, block value);
    block getBlock(int x, int y);
    void genOutputTexture();
    void GenInitialSurface(bool producePictures);
    void FillOcean(bool producePictures);
    Color blockColors[4] = {GetColor(0), GRAY, BROWN, BLUE};
    int cheapDrawCycle = 0;

public:
    GameWorld(int seed, int width, int height);
    void draw(bool fullFrame);
    void drawCheap();
    void genWorld(bool producePictures);
    void clearWorld(block with);

    int getSeed();
    void setSeed(int val);

    void genHeightmap();
};


#endif //INC_2DPROCEDUALGEN_GAMEWORLD_H
