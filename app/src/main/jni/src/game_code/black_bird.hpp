#ifndef _BLACKBIRD_HPP_
#define _BLACKBIRD_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "gtexture.hpp";

class BlackBird {
public:

    BlackBird();

    BlackBird(SDL_Renderer *renderer, std::string idleTexName, float _bflyW, float _bflyH);

    ~BlackBird();

    void update(float deltaTime, int gameW, int gameH);

    void draw(SDL_Renderer *renderer, SDL_Rect *camrect);

    void setPos(int x, int y);

    void dispose();

    SDL_Rect *getCurrFrameRect();

private:
    GTexture idleTex;

    SDL_Vector position = SDL_Vector(0, 0, 0);

    SDL_Rect currFrameRect;

    int bflyW = 180, bflyH = 120;

    int counter = 0;

    bool goingright = true;

};

#endif