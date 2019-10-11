#include "walking_alien.hpp"

WalkingAlien::WalkingAlien() {

}

WalkingAlien::WalkingAlien(SDL_Renderer *renderer, std::string idleTexName, float _alienW,
                           float _alienH) {

    idleTex = GTexture(renderer, idleTexName, 0.0f);
    idleTex.setupRect(0, 0, _alienW, _alienH);

    currFrameRect = {this->alienW, 0, this->alienW, this->alienH};
}

void WalkingAlien::update() {
    counter++;
    if (counter == 15) {
        counter = 0;

        currFrameRect.x += this->alienW;

        if (currFrameRect.x > 880) {
            currFrameRect.x = 0;
        }

    }
}

void WalkingAlien::draw(SDL_Renderer *renderer, SDL_Rect *camrect) {
    idleTex.draw(renderer, &currFrameRect, idleTex.getTexRect(), camrect, 0.0f);
}

void WalkingAlien::draw(SDL_Renderer *renderer, SDL_Rect *camrect, int flip) {
    idleTex.draw(renderer, &currFrameRect, idleTex.getTexRect(), camrect, 0.0f,
                 SDL_FLIP_HORIZONTAL);
}

SDL_Rect *WalkingAlien::getCurrFrameRect() {
    return &currFrameRect;
}

GTexture *WalkingAlien::getTex() {
    return &idleTex;
}

void WalkingAlien::setPos(int x, int y) {
    idleTex.getTexRect()->x = x;
    idleTex.getTexRect()->y = y;
}

void WalkingAlien::dispose() {
    idleTex.destroyTex();
}

WalkingAlien::~WalkingAlien() {

}