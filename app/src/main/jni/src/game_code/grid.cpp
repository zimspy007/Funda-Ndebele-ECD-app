#include "grid.hpp"

Grid::Grid() {

}

Grid::Grid(int scrnW, int scrnH) {
    lvlwidth = (scrnW * 0.925f);
    lvlheight = (scrnH * 0.925f);

    cardheight = lvlheight * 0.375f;
    cardwidth = cardheight /*lvlwidth * 0.25f*/;

    float cardGap = float(cardwidth * 0.2f);

    lvlX = (scrnW / 2) - (cardwidth / 2);
    float lvlMid = scrnH / 2;
    lvlY = cardheight + (cardwidth * 0.45f);

    // set the card positions
    float cardsXpos = lvlX + cardwidth;

    lowerpos2 = SDL_Vector(lvlX, lvlY, 0.0f);
    lowerpos1 = SDL_Vector(lvlX - (cardwidth + cardGap), lvlY, 0.0f);
    lowerpos3 = SDL_Vector(lvlX + (cardwidth + cardGap), lvlY, 0.0f);

    upperpos2 = SDL_Vector(lvlX, lvlY - (cardheight * 0.05f) - cardheight, 0.0f);
    upperpos1 = SDL_Vector(lvlX - (cardwidth + cardGap), upperpos2.y, 0.0f);
    upperpos3 = SDL_Vector(lvlX + (cardwidth + cardGap), upperpos2.y, 0.0f);

}

float Grid::getCardwidth() {
    return cardwidth;
}

float Grid::getCardheight() {
    return cardheight;
}

SDL_Vector Grid::getLowerpos1() {
    return lowerpos1;
}

SDL_Vector Grid::getLowerpos2() {
    return lowerpos2;
}

SDL_Vector Grid::getLowerpos3() {
    return lowerpos3;
}

SDL_Vector Grid::getUpperpos1() {
    return upperpos1;
}

SDL_Vector Grid::getUpperpos2() {
    return upperpos2;
}

SDL_Vector Grid::getUpperpos3() {
    return upperpos3;
}

Grid::~Grid() {

}