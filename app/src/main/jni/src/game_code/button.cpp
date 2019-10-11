#include "button.hpp"

Button::Button() {}

Button::Button(SDL_Renderer *renderer, std::string filename, int w, int h) {
    btnTex = GTexture(renderer, filename, 0.0f);

    btnTex.setupRect(0, 0, w, h);
}

Button::~Button() {}

void Button::draw(SDL_Renderer *renderer, SDL_Rect *camRect) {
    this->btnTex.draw(renderer, this->btnTex.getTexRect(), camRect, 0.0f);
}

SDL_Vector Button::getPos() {
    return this->pos;
}

SDL_Rect *Button::getBtnRect() {
    return btnTex.getTexRect();
}

GTexture *Button::getbtnTex() {
    return &btnTex;
}

void Button::setPos(SDL_Vector pos) {
    this->pos = pos;
    this->btnTex.getTexRect()->x = pos.x;
    this->btnTex.getTexRect()->y = pos.y;
}

void Button::disposeTex() {
    btnTex.destroyTex();
}