#ifndef _PUZLE_HPP
#define _PUZZLE_HPP

#include <string>
#include <stdlib.h>
#include <sstream>

#include "card.hpp"
#include "grid.hpp"
#include "tinyxml/tinyxml.h"

class Puzzle {
public:

    Puzzle();

    Puzzle(SDL_Renderer *renderer, Grid *grid, std::string puzzledata);

    ~Puzzle();

    Card getTopCard();

    Card getLowerCard1();

    Card getLowerCard2();

    Card getLowerCard3();

    std::string getSolution();

    std::string getPuzzleSound();

    int getLevel();

    int getNextLevel();

    void draw(SDL_Renderer *renderer, SDL_Rect *camrect);

    void dispose();

private:
    Card topcard1;

    Card bottomcard1;
    Card bottomcard2;
    Card bottomcard3;

    std::string solution;
    std::string sound;
    int level;

    template<typename T>
    std::string to_string(T value) {
        std::ostringstream os;
        os << value;
        return os.str();
    }

};

#endif