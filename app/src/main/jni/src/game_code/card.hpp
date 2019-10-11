#ifndef _CARD_HPP_
#define _CARD_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "gtexture.hpp"
#include "grid.hpp"
#include "sdl_vector.hpp"

class Card {
public:

    Card();

    Card(SDL_Renderer *renderer, Grid *grid, std::string path);

    ~Card();

    void draw(SDL_Renderer *renderer, SDL_Rect *camRect);

    GTexture *getTex();

    std::string getName();

    SDL_Vector getPos();

    void setPos(SDL_Vector pos);

    void setPos(int x, int y);

private:
    GTexture cardTex;

    std::string name;

    bool isclicked = false;
};

#endif