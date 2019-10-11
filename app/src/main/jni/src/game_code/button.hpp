#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include <string.h>

#include "gtexture.hpp"
#include "sdl_vector.hpp"

class Button {
public:

    Button();

    Button(SDL_Renderer *renderer, std::string filename, int w, int h);

    ~Button();

    void draw(SDL_Renderer *renderer, SDL_Rect *camRect);

    SDL_Vector getPos();

    SDL_Rect *getBtnRect();

    GTexture *getbtnTex();

    void setPos(SDL_Vector pos);

    void disposeTex();

private:

    GTexture btnTex;

    SDL_Vector pos;

};

#endif