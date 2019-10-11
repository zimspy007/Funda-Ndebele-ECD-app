#ifndef _PINK_TREE_HPP_
#define _PINK_TREE_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "gtexture.hpp";

class PinkTree {
public:

    PinkTree();

    PinkTree(SDL_Renderer *renderer, std::string idleTexName, float _treeW, float _treeH);

    ~PinkTree();

    void update(int _counter);

    void draw(SDL_Renderer *renderer, SDL_Rect *camrect);

    void setPos(int x, int y);

    void dispose();

    SDL_Rect *getCurrFrameRect();

private:
    GTexture idleTex;

    SDL_Vector position = SDL_Vector(0, 0, 0);

    SDL_Rect currFrameRect;

    int treeW = 271, treeH = 240;

    int counter = 0;

};

#endif