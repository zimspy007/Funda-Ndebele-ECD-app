#include "black_bird.hpp"

BlackBird::BlackBird() {

}

BlackBird::BlackBird(SDL_Renderer *renderer, std::string idleTexName, float _bflyW, float _bflyH) {

    idleTex = GTexture(renderer, idleTexName, 0.0f);
    idleTex.setupRect(0, 0, _bflyW, _bflyH);

    currFrameRect = {this->bflyW, 0, this->bflyW, this->bflyH};
}

void BlackBird::update(float deltaTime, int gameW, int gameH) {
    counter++;
    if (counter == 15) {
        counter = 0;

        currFrameRect.x += this->bflyW;

        if (currFrameRect.x > (420)) {
            currFrameRect.x = 0;
        }
    }

    this->setPos(this->position.x += 2, this->position.y);

    if (this->position.x > gameW + (gameW * 0.5f)) {
        this->position.x = 0 - (gameW * 0.5f);

        int rndY = rand() % (gameH + bflyH);
        this->position.y = rndY;

        goingright = false;
    }
}

void BlackBird::draw(SDL_Renderer *renderer, SDL_Rect *camrect) {
    idleTex.draw(renderer, &currFrameRect, idleTex.getTexRect(), camrect, 0.0f);
}

SDL_Rect *BlackBird::getCurrFrameRect() {
    return &currFrameRect;
}

void BlackBird::setPos(int x, int y) {
    idleTex.getTexRect()->x = x;
    idleTex.getTexRect()->y = y;

    this->position = SDL_Vector(x, y, 0);
}

void BlackBird::dispose() {
    idleTex.destroyTex();
}

BlackBird::~BlackBird() {

}