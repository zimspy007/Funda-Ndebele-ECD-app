#include "puzzle.hpp"

Puzzle::Puzzle() {
}

Puzzle::Puzzle(SDL_Renderer *renderer, Grid *grid, std::string puzzledata) {
    TiXmlDocument doc;

    bool loadSuccess = doc.Parse(puzzledata.c_str());;

    TiXmlElement *_dataElement = doc.FirstChildElement("PuzzleData");
    if (!_dataElement) exit(1);

    TiXmlElement *saveDataElement = _dataElement->FirstChildElement("Puzzle1");
    if (!saveDataElement) exit(1);

    std::string topcard1cstr = std::string("media/puzzle_data/") +
                               _dataElement->FirstChildElement("Puzzle1")->Attribute("topcard1");
    topcard1 = Card(renderer, grid, topcard1cstr);

    std::string bottomcard1cstr = std::string("media/puzzle_data/") +
                                  _dataElement->FirstChildElement("Puzzle1")->Attribute(
                                          "bottomcard1");
    bottomcard1 = Card(renderer, grid, bottomcard1cstr);

    std::string bottomcard2cstr = std::string("media/puzzle_data/") +
                                  _dataElement->FirstChildElement("Puzzle1")->Attribute(
                                          "bottomcard2");
    bottomcard2 = Card(renderer, grid, bottomcard2cstr);

    std::string bottomcard3cstr = std::string("media/puzzle_data/") +
                                  _dataElement->FirstChildElement("Puzzle1")->Attribute(
                                          "bottomcard3");
    bottomcard3 = Card(renderer, grid, bottomcard3cstr);

    solution = _dataElement->FirstChildElement("Puzzle1")->Attribute("solution");

    sound = _dataElement->FirstChildElement("Puzzle1")->Attribute("sound");

    _dataElement->FirstChildElement("Puzzle1")->QueryIntAttribute("level", &level);

    topcard1.getTex()->setPos(grid->getUpperpos2());

    bottomcard1.setPos(grid->getLowerpos1());
    bottomcard2.setPos(grid->getLowerpos2());
    bottomcard3.setPos(grid->getLowerpos3());

}

Puzzle::~Puzzle() {

}

int Puzzle::getLevel() {
    return level;
}

int Puzzle::getNextLevel() {
    return level + 1;
}

Card Puzzle::getTopCard() {
    return topcard1;
}

Card Puzzle::getLowerCard1() {
    return this->bottomcard1;
}

Card Puzzle::getLowerCard2() {
    return this->bottomcard2;
}

Card Puzzle::getLowerCard3() {
    return this->bottomcard3;
}

std::string Puzzle::getSolution() {
    return solution;
}

std::string Puzzle::getPuzzleSound() {
    return this->sound;
}

void Puzzle::draw(SDL_Renderer *renderer, SDL_Rect *camrect) {
    topcard1.draw(renderer, camrect);

    bottomcard1.draw(renderer, camrect);
    bottomcard2.draw(renderer, camrect);
    bottomcard3.draw(renderer, camrect);
}

void Puzzle::dispose() {
    topcard1.getTex()->destroyTex();
    bottomcard1.getTex()->destroyTex();
    bottomcard2.getTex()->destroyTex();
    bottomcard3.getTex()->destroyTex();
}