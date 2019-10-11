#include "butterfly.hpp"

Butterfly::Butterfly() {

}

Butterfly::Butterfly(SDL_Renderer *renderer, std::string idleTexName, float _bflyW, float _bflyH) {

    idleTex = GTexture(renderer, idleTexName, 0.0f);
    idleTex.setupRect(0, 0, _bflyW, _bflyH);

    currFrameRect = {this->bflyW, 0, this->bflyW, this->bflyH};
}

void Butterfly::update(float deltaTime, int gameW, int gameH) {
    counter++;
    if (counter == 10) {
        counter = 0;

        currFrameRect.x += this->bflyW;

        if (currFrameRect.x > (630)) {
            currFrameRect.x = 0;
        }
    }

    if (goingup) {
        this->setPos(this->position.x -= 1, this->position.y - 1);

        if (this->position.x < 0) {
            this->position.x = gameW;

            int rndY = rand() % (gameH + bflyH);
            this->position.y = rndY;

            goingup = false;
        }
    } else {
        this->setPos(this->position.x -= 1, this->position.y + 1);

        if (this->position.x < 0) {
            this->position.x = gameW;

            int rndY = rand() % (gameH + bflyH);
            this->position.y = rndY;

            goingup = true;
        }
    }

}

void Butterfly::draw(SDL_Renderer *renderer, SDL_Rect *camrect) {
    idleTex.draw(renderer, &currFrameRect, idleTex.getTexRect(), camrect, 0.0f);
}

SDL_Rect *Butterfly::getCurrFrameRect() {
    return &currFrameRect;
}

void Butterfly::setPos(int x, int y) {
    idleTex.getTexRect()->x = x;
    idleTex.getTexRect()->y = y;

    this->position = SDL_Vector(x, y, 0);
}

void Butterfly::dispose() {
    idleTex.destroyTex();
}

Butterfly::~Butterfly() {

}