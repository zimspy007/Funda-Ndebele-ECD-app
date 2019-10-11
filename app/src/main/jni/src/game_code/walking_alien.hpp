#ifndef _WALKING_ALIEN_HPP_
#define _WALKING_ALIEN_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "gtexture.hpp";

class WalkingAlien {
public :

    WalkingAlien();

    WalkingAlien(SDL_Renderer *renderer, std::string idleTexName, float _alienW, float _alienH);

    ~WalkingAlien();

    void update();

    void draw(SDL_Renderer *renderer, SDL_Rect *camrect);

    void draw(SDL_Renderer *renderer, SDL_Rect *camrect, int flip);

    void setPos(int x, int y);

    void dispose();

    SDL_Rect *getCurrFrameRect();

    GTexture *getTex();

private :
    GTexture idleTex;

    SDL_Vector position = SDL_Vector(0, 0, 0);

    SDL_Rect currFrameRect;

    int alienW = 176, alienH = 430;

    int counter = 0;
};

#endif