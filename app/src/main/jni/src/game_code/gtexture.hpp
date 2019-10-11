#ifndef _GTEXTURE_HPP
#define _GTEXTURE_HPP

#include "game.hpp"
#include "sdl_vector.hpp"

class GTexture {
public:
    GTexture();

    GTexture(SDL_Renderer *renderer, std::string filename, float angle);

    ~GTexture();

    void setupRect(int x, int y, int w, int h);

    void destroyTex();

    void setPos(int x, int y);

    void setPos(SDL_Vector pos);

    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    void setAlpha(Uint8 alpha);

    void setBlendMode(SDL_BlendMode blending);

    void setRect(SDL_Rect rect);

    int getTextureW();

    int getTextureH();

    SDL_Rect *getTexRect();

    SDL_Texture *getTex();

    void draw(SDL_Renderer *renderer, SDL_Rect *sprRect, SDL_Rect *camRect, float angle);

    void draw(SDL_Renderer *renderer, int x, int y, SDL_Rect *sprRect, SDL_Rect *camRect);

    void draw(SDL_Renderer *renderer, SDL_Rect *sprRect, SDL_Rect *camRect, float angle,
              SDL_RendererFlip flip);

    void draw(SDL_Renderer *renderer, SDL_Rect *srcRect, SDL_Rect *sprRect, SDL_Rect *camRect,
              float angle);

    void draw(SDL_Renderer *renderer, int x, int y, SDL_Rect *srcRect, SDL_Rect *sprRect,
              SDL_Rect *camRect);

    void draw(SDL_Renderer *renderer, SDL_Rect *srcRect, SDL_Rect *sprRect, SDL_Rect *camRect,
              float angle, SDL_RendererFlip flip);

private:
    int x;
    int y;
    int width;
    int height;

    SDL_Rect texRect;
    SDL_Texture *tex;
};

#endif _GTEXTURE_HPP
