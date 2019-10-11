#include "alien.hpp"

Alien::Alien() {

}

Alien::Alien(SDL_Renderer *renderer, std::string idleTexName, float _alienW, float _alienH) {

    idleTex = GTexture(renderer, idleTexName, 0.0f);
    idleTex.setupRect(0, 0, _alienW, _alienH);

    currFrameRect = {this->alienW, 0, this->alienW, this->alienH};
}

void Alien::update() {
    counter++;
    if (counter == 100) {
        counter = 0;

        currFrameRect.x += this->alienW;

        if (currFrameRect.x > (this->alienW)) {
            currFrameRect.x = 0;
        }

    }
}

void Alien::draw(SDL_Renderer *renderer, SDL_Rect *camrect) {
    idleTex.draw(renderer, &currFrameRect, idleTex.getTexRect(), camrect, 0.0f);
}

SDL_Rect *Alien::getCurrFrameRect() {
    return &currFrameRect;
}

void Alien::setPos(int x, int y) {

    idleTex.getTexRect()->x = x;
    idleTex.getTexRect()->y = y;
}

void Alien::dispose() {
    idleTex.destroyTex();
}

Alien::~Alien() {

}