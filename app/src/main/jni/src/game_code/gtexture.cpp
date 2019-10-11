#include "gtexture.hpp"

GTexture::GTexture() {

}

GTexture::GTexture(SDL_Renderer *renderer, std::string filename, float angle) {
    SDL_Surface *tmpSurface = IMG_Load(filename.c_str());

    if (tmpSurface == NULL) {
        std::cout << "Could not load image " << filename << " : " << IMG_GetError() << std::endl;
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_VERBOSE, "Could not load image ", IMG_GetError());
#endif
    } else {
        if (tmpSurface->format->Amask) {
        } else {
            SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0xFF, 0x00, 0xFF));
        }

        //Create texture from surface pixels
        this->tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);

        if (this->tex == NULL) {
            std::cout << "Could not create texture from " << filename << " : " << SDL_GetError()
                      << std::endl;
#ifdef __ANDROID__
            __android_log_print(ANDROID_LOG_VERBOSE, "Could not create texture from ",
                                SDL_GetError());
#endif
        } else {
            this->width = tmpSurface->w;
            this->height = tmpSurface->h;
            this->x = 0;
            this->y = 0;

            this->texRect = {x, y, width, height};
        }

        SDL_FreeSurface(tmpSurface);
    }
}

void GTexture::setupRect(int x, int y, int w, int h) {
    this->texRect.x = x;
    this->texRect.y = y;
    this->texRect.w = w;
    this->texRect.h = h;
}

void GTexture::destroyTex() {
    SDL_DestroyTexture(this->tex);
    this->tex = NULL;
    this->width = 0;
    this->height = 0;
}

void GTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    //Modulate texture rgb
    SDL_SetTextureColorMod(this->tex, red, green, blue);
}

void GTexture::setBlendMode(SDL_BlendMode blending) {
    //Set blending function
    SDL_SetTextureBlendMode(this->tex, blending);
}

void GTexture::setAlpha(Uint8 alpha) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(this->tex, alpha);
}

void GTexture::setPos(int x, int y) {
    this->texRect.x = x;
    this->texRect.y = y;
}

void GTexture::setPos(SDL_Vector pos) {
    this->texRect.x = pos.x;
    this->texRect.y = pos.y;
}

void GTexture::setRect(SDL_Rect rect) {
    this->texRect = rect;
}

int GTexture::getTextureW() {
    return this->width;
}

int GTexture::getTextureH() {
    return this->height;
}

SDL_Rect *GTexture::getTexRect() {
    return &this->texRect;
}

SDL_Texture *GTexture::getTex() {
    return this->tex;
}

GTexture::~GTexture() {

}

void GTexture::draw(SDL_Renderer *renderer, SDL_Rect *sprRect, SDL_Rect *camRect, float angle) {

    SDL_Rect drawingRect = {sprRect->x - camRect->x, sprRect->y - camRect->y, sprRect->w,
                            sprRect->h};

    SDL_RenderCopyEx(renderer, this->tex, NULL, &drawingRect, angle, nullptr, SDL_FLIP_NONE);
}

void GTexture::draw(SDL_Renderer *renderer, int _x, int _y, SDL_Rect *sprRect, SDL_Rect *camRect) {

    SDL_Rect drawingRect = {_x - camRect->x, _y - camRect->y, sprRect->w, sprRect->h};

    SDL_RenderCopyEx(renderer, this->tex, NULL, &drawingRect, 0.0f, nullptr, SDL_FLIP_NONE);
}

void GTexture::draw(SDL_Renderer *renderer, SDL_Rect *sprRect, SDL_Rect *camRect, float angle,
                    SDL_RendererFlip flip) {

    SDL_Rect drawingRect = {sprRect->x - camRect->x, sprRect->y - camRect->y, sprRect->w,
                            sprRect->h};

    SDL_RenderCopyEx(renderer, this->tex, NULL, &drawingRect, angle, nullptr, flip);
}

void GTexture::draw(SDL_Renderer *renderer, SDL_Rect *srcRect, SDL_Rect *sprRect, SDL_Rect *camRect,
                    float angle) {
    SDL_Rect drawingRect = {sprRect->x - camRect->x, sprRect->y - camRect->y, sprRect->w,
                            sprRect->h};

    SDL_RenderCopyEx(renderer, this->tex, srcRect, &drawingRect, angle, nullptr, SDL_FLIP_NONE);
}

void GTexture::draw(SDL_Renderer *renderer, int x, int y, SDL_Rect *srcRect, SDL_Rect *sprRect,
                    SDL_Rect *camRect) {
    SDL_Rect drawingRect = {sprRect->x - camRect->x, sprRect->y - camRect->y, sprRect->w,
                            sprRect->h};

    SDL_RenderCopyEx(renderer, this->tex, srcRect, &drawingRect, 0.0f, nullptr, SDL_FLIP_NONE);
}

void GTexture::draw(SDL_Renderer *renderer, SDL_Rect *srcRect, SDL_Rect *sprRect, SDL_Rect *camRect,
                    float angle, SDL_RendererFlip flip) {
    SDL_Rect drawingRect = {sprRect->x - camRect->x, sprRect->y - camRect->y, sprRect->w,
                            sprRect->h};

    SDL_RenderCopyEx(renderer, this->tex, srcRect, &drawingRect, angle, nullptr, flip);
}
