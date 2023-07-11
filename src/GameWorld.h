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
    int width;
    int height;
    int seed;
    Image heightMap;
    RenderTexture heightMapTex;
    RenderTexture outputTexture;
    void setBlock(int x, int y, block value);
    block getBlock(int x, int y);
    void genOutputTexture();
    void GenInitialSurface();
    void FillUnderGround();
    void FillOcean();


public:
    GameWorld(int seed, int width, int height);
    void draw(bool fullFrame);


};


#endif //INC_2DPROCEDUALGEN_GAMEWORLD_H
