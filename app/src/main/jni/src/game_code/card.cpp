#include "card.hpp"

Card::Card() {

}

Card::Card(SDL_Renderer *renderer, Grid *grid, std::string path) {
    cardTex = GTexture(renderer, path, 0.0f);
    cardTex.setupRect(0, 0, grid->getCardwidth(), grid->getCardheight());

    std::size_t found = path.find_last_of("/");
    name = path.substr(found + 1);

    found = name.find_last_of(".");
    name = name = name.substr(0, found);
}

GTexture *Card::getTex() {
    return &cardTex;
}

void Card::draw(SDL_Renderer *renderer, SDL_Rect *camRect) {
    cardTex.draw(renderer, cardTex.getTexRect(), camRect, 0.0f);
}

std::string Card::getName() {
    return name;
}

SDL_Vector Card::getPos() {
    SDL_Vector _pos = SDL_Vector(this->cardTex.getTexRect()->x, this->cardTex.getTexRect()->y, 0);
    return _pos;
}

void Card::setPos(SDL_Vector pos) {
    this->cardTex.getTexRect()->x = pos.x;
    this->cardTex.getTexRect()->y = pos.y;
}

void Card::setPos(int x, int y) {
    this->cardTex.getTexRect()->x = x;
    this->cardTex.getTexRect()->y = y;
}

Card::~Card() {

}