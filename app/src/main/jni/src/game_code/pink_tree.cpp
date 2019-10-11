#include "pink_tree.hpp"

PinkTree::PinkTree() {

}

PinkTree::PinkTree(SDL_Renderer *renderer, std::string idleTexName, float _treeW, float _treeH) {

    idleTex = GTexture(renderer, idleTexName, 0.0f);
    idleTex.setupRect(0, 0, _treeW, _treeH);

    currFrameRect = {this->treeW, 0, this->treeW, this->treeH};
}

void PinkTree::update(int _counter) {
    counter++;
    if (counter == _counter) {
        counter = 0;

        currFrameRect.x += this->treeW;

        if (currFrameRect.x > (4065 - treeW)) {
            currFrameRect.x = 0;
        }
    }

}

void PinkTree::draw(SDL_Renderer *renderer, SDL_Rect *camrect) {
    idleTex.draw(renderer, &currFrameRect, idleTex.getTexRect(), camrect, 0.0f);
}

SDL_Rect *PinkTree::getCurrFrameRect() {
    return &currFrameRect;
}

void PinkTree::setPos(int x, int y) {
    idleTex.getTexRect()->x = x;
    idleTex.getTexRect()->y = y;

    this->position = SDL_Vector(x, y, 0);
}

void PinkTree::dispose() {
    idleTex.destroyTex();
}

PinkTree::~PinkTree() {

}