#ifndef _FIREWORK_HPP_
#define _FIREWORK_HPP_

#include <algorithm>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>

#include "game.hpp"
#include "particle.hpp"

#define PI 3.1415926

class mFirework {
public:

    mFirework();

    mFirework(SDL_Renderer *renderer, int w, int h, int amnt);

    ~mFirework();

    /*fix this*/
    FireworkParticle particle[20];
    SDL_Texture *circles[6];

    int getCx();

    int getCy();

    int getR();

    int getAmnt();

    void setCx(int _val);

    void setCy(int _val);

    void setR(int _val);

    void setAmnt(int _val);

    void updateFirework();

    void sketchFirework(SDL_Renderer *renderer, SDL_Rect *rect);

    void destroyFirework();

private:
    int cX;
    int cY;
    int r;
    int amount;
    SDL_Texture *circle;
    SDL_Rect rectCircle;

    void initFirework(int w, int h);

};

#endif