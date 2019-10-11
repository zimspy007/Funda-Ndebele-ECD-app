#ifndef _GRID_HPP__
#define _GRID_HPP__

#include "sdl_vector.hpp"

class Grid {
public:

    Grid();

    Grid(int scrnW, int scrnH);

    ~Grid();

    SDL_Vector getUpperpos1();

    SDL_Vector getUpperpos2();

    SDL_Vector getUpperpos3();

    SDL_Vector getLowerpos1();

    SDL_Vector getLowerpos2();

    SDL_Vector getLowerpos3();

    float getCardwidth();

    float getCardheight();

private:
    SDL_Vector lowerpos1;
    SDL_Vector lowerpos2;
    SDL_Vector lowerpos3;

    SDL_Vector upperpos1;
    SDL_Vector upperpos2;
    SDL_Vector upperpos3;

    float cardwidth, cardheight;
    float lvlwidth, lvlheight;
    float lvlX, lvlY;

};


#endif