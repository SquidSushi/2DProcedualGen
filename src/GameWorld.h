//
// Created by mrbau on 11.07.2023.
//

#ifndef INC_2DPROCEDUALGEN_GAMEWORLD_H
#define INC_2DPROCEDUALGEN_GAMEWORLD_H

enum block{
    block_air,
    block_stone,
    block_dirt
};

class GameWorld {
    block* data;
    int width;
    int height;
    int seed;
    Texture2D heightMap;
    GameWorld(int seed, int width, int height);
};


#endif //INC_2DPROCEDUALGEN_GAMEWORLD_H
