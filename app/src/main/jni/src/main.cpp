#include "game_code/puzzle_data.hpp"
#include "game_code/game.hpp"
#include "game_code/grid.hpp"
#include "game_code/card.hpp"
#include "game_code/puzzle.hpp"
#include "game_code/alien.hpp"
#include "game_code/walking_alien.hpp"
#include "game_code/black_bird.hpp"
#include "game_code/butterfly.hpp"
#include "game_code/pink_tree.hpp"
#include "game_code/firework.hpp"
#include "game_code/button.hpp"

#ifdef __ANDROID__
#endif //__ANDROID__

/*amount of fireworks to use for fireworks effect*/
#define AMOUNT 18

/*destroys sdl textures and frees up memory*/
void destroyTextures();

/*loads all media into memory, returns true if successful*/
bool loadmedia();

void processInput(SDL_Point _point);

bool showFireworks = false;

/*pointer to the game object*/
Game *game;

/*the camera object. used to project screen to a specific rect but only useful for scrolling screens*/
Camera cam;

Grid grid;

GTexture bgTex;
GTexture forestbg;
GTexture scrnTex;
GTexture schoolTex;

GTexture creditsTex;

Card clickCard;

Alien alien;
WalkingAlien walkingalien;
Butterfly bfly;
BlackBird blackbird;
PinkTree pinktree;
PinkTree greentree;

int MAX_LEVEL = 45;
int puzzles_index = 0;

Puzzle currPuzzle, oldPuzzle;

int puzzleCounter = 0;
bool updatePuzzle = false;

Button btnquit;
Button btninfo;
Button btnPlay;

Mix_Chunk *eff_help;
Mix_Chunk *eff_hello;
Mix_Chunk *eff_tools;
Mix_Chunk *eff_correct;
Mix_Chunk *eff_retry;

mFirework fire[AMOUNT];

const int GAME_STATE_MENU = 10;
const int GAME_STATE_CREDITS = 20;
const int GAME_STATE_LOADING = 30;
const int GAME_STATE_EXITING = 40;
const int GAME_STATE_3PUZZLE = 50;

int GAME_STATE = GAME_STATE_MENU;

int main(int argc, char *argv[]) {
    game = new Game();

    grid = Grid(game->getScrnW(), game->getScrnH());

    cam = Camera(game->getScrnW(), game->getScrnH());

    std::random_shuffle(puzzles, puzzles + sizeof(puzzles) / sizeof(puzzles[0]));

    //load game stuff here
    if (!loadmedia())
        exit(2);

    //Center the camera over the screen
    cam.camRect.x = 0;
    cam.camRect.y = 0;

    game->runGame();

    destroyTextures();
    game->shutdown();
    exit(0);
}

void destroyTextures() {
    bgTex.destroyTex();
    forestbg.destroyTex();
    scrnTex.destroyTex();
    schoolTex.destroyTex();
    creditsTex.destroyTex();

    clickCard.getTex()->destroyTex();

    currPuzzle.dispose();

    alien.dispose();
    walkingalien.dispose();
    bfly.dispose();
    blackbird.dispose();

    pinktree.dispose();
    greentree.dispose();

    for (int i = 0; i < AMOUNT; i++) {
        fire[i].destroyFirework();
    }

    btnPlay.disposeTex();
    btnquit.disposeTex();
    btninfo.disposeTex();

    Mix_FreeChunk(eff_hello);
    Mix_FreeChunk(eff_help);
    Mix_FreeChunk(eff_tools);
    Mix_FreeChunk(eff_correct);
    Mix_FreeChunk(eff_retry);
}

/*implementation of global function declared in game.cpp*/
void updateGame(float deltaTime) {
    switch (GAME_STATE) {
        case GAME_STATE_MENU:

            bfly.update(deltaTime, game->getScrnW(), game->getScrnH());
            blackbird.update(deltaTime, game->getScrnW(), game->getScrnH());

            pinktree.update(150);
            greentree.update(265);

            break;

        case GAME_STATE_CREDITS:
            alien.update();

            break;

        case GAME_STATE_LOADING:
            if (walkingalien.getTex()->getTexRect()->x < game->getScrnW()) {
                walkingalien.setPos(walkingalien.getTex()->getTexRect()->x + 2,
                                    walkingalien.getTex()->getTexRect()->y);
            } else {
                GAME_STATE = GAME_STATE_3PUZZLE;

                Mix_PlayChannel(-1, eff_help, 0);
            }
            walkingalien.update();

            break;

        case GAME_STATE_EXITING:
            if (walkingalien.getTex()->getTexRect()->x > 0) {
                walkingalien.setPos(walkingalien.getTex()->getTexRect()->x - 2,
                                    walkingalien.getTex()->getTexRect()->y);
            } else {
                GAME_STATE = GAME_STATE_MENU;
            }
            walkingalien.update();

            break;

        case GAME_STATE_3PUZZLE:

            if (showFireworks) {
                for (int i = 0; i < AMOUNT; i++) {
                    fire[i].updateFirework();
                }
            }

            alien.update();

            if (updatePuzzle) {
                puzzleCounter++;

                if (puzzleCounter == 275) {
                    updatePuzzle = false;
                    puzzleCounter = 0;
                    showFireworks = false;

                    clickCard.setPos(grid.getUpperpos2().x, grid.getUpperpos2().y);

                    puzzles_index++;
                    if (puzzles_index < MAX_LEVEL + 1) {
                        oldPuzzle = currPuzzle;

                        Puzzle puzzle = Puzzle(game->getRenderer(), &grid, puzzles[puzzles_index]);
                        currPuzzle = puzzle;
                        oldPuzzle.dispose();

                        eff_help = Mix_LoadWAV(puzzle.getPuzzleSound().c_str());

                    } else {
                        puzzles_index = 0;

                        oldPuzzle = currPuzzle;

                        Puzzle puzzle = Puzzle(game->getRenderer(), &grid, puzzles[puzzles_index]);
                        currPuzzle = puzzle;
                        oldPuzzle.dispose();

                        eff_help = Mix_LoadWAV(puzzle.getPuzzleSound().c_str());
                    }

                    /*Use puzzleType to play a sound and introduce the puzzle*/
                    Mix_PlayChannel(-1, eff_help, 0);

                }
            }
            break;
        default:
            break;
    }
}

/*implementation of global function declared in game.cpp*/
void drawGame() {
    switch (GAME_STATE) {
        case GAME_STATE_MENU:
            forestbg.draw(game->getRenderer(), forestbg.getTexRect(), &cam.camRect, 0.0f);

            pinktree.draw(game->getRenderer(), &cam.camRect);
            greentree.draw(game->getRenderer(), &cam.camRect);

            btnPlay.draw(game->getRenderer(), &cam.camRect);

            bfly.draw(game->getRenderer(), &cam.camRect);
            blackbird.draw(game->getRenderer(), &cam.camRect);

            btninfo.draw(game->getRenderer(), &cam.camRect);

            btnquit.draw(game->getRenderer(), &cam.camRect);

            break;

        case GAME_STATE_CREDITS:
            creditsTex.draw(game->getRenderer(), creditsTex.getTexRect(), &cam.camRect, 0.0f);

            alien.draw(game->getRenderer(), &cam.camRect);

            break;

        case GAME_STATE_LOADING:
            schoolTex.draw(game->getRenderer(), schoolTex.getTexRect(), &cam.camRect, 0.0f);
            walkingalien.draw(game->getRenderer(), &cam.camRect);
            break;

        case GAME_STATE_EXITING:
            schoolTex.draw(game->getRenderer(), schoolTex.getTexRect(), &cam.camRect, 0.0f);
            walkingalien.draw(game->getRenderer(), &cam.camRect, -1);
            break;

        case GAME_STATE_3PUZZLE:
            bgTex.draw(game->getRenderer(), bgTex.getTexRect(), &cam.camRect, 0.0f);
            scrnTex.draw(game->getRenderer(), scrnTex.getTexRect(), &cam.camRect, 0.0f);

            alien.draw(game->getRenderer(), &cam.camRect);

            currPuzzle.draw(game->getRenderer(), &cam.camRect);

            clickCard.draw(game->getRenderer(), &cam.camRect);

            if (showFireworks) {
                //
                for (int i = 0; i < AMOUNT; i++) {
                    fire[i].sketchFirework(game->getRenderer(), &cam.camRect);
                }
            }

            break;
        default:
            break;
    }
}

bool loadmedia() {
    bool success = false;

    schoolTex = GTexture(game->getRenderer(), "media/images/school.png", 0.0f);
    schoolTex.setupRect(0, 0, game->getScrnW(), game->getScrnH());

    bgTex = GTexture(game->getRenderer(), "media/images/winter_bg.png", 0.0f);
    bgTex.setupRect(0, 0, game->getScrnW(), game->getScrnH());

    forestbg = GTexture(game->getRenderer(), "media/images/forest.jpg", 0.0f);
    forestbg.setupRect(0, 0, game->getScrnW(), game->getScrnH());

    creditsTex = GTexture(game->getRenderer(), "media/images/credits.png", 0.0f);
    creditsTex.setupRect(0, 0, game->getScrnW(), game->getScrnH());

    scrnTex = GTexture(game->getRenderer(), "media/images/screen.png", 0.0f);

    float scrW = float(game->getScrnW() * 0.975f);
    float scrH = float(game->getScrnH() * 0.975f);
    int scrX = (game->getScrnW() / 2) - (scrW / 2);
    int scrY = (game->getScrnH() / 2) - (scrH / 2);
    scrnTex.setupRect(scrX, scrY, scrW, scrH);

    clickCard = Card(game->getRenderer(), &grid, "media/images/clickcard.png");
    clickCard.setPos(grid.getUpperpos2().x, grid.getUpperpos2().y);

    //calculate image rect dimensions
    /*int cardW = 400, cardH = 400;
    float cardDimens = grid.getCardwidth();*/

    float imgScale = float(grid.getCardwidth() / clickCard.getTex()->getTextureW());

    alien = Alien(game->getRenderer(), "media/images/alien/alien_idle.png", imgScale * 213,
                  imgScale * 400);
    alien.setPos(0, game->getScrnH() - (imgScale * 400));

    walkingalien = WalkingAlien(game->getRenderer(), "media/images/alien/alien_walk.png",
                                imgScale * 176, imgScale * 430);
    walkingalien.setPos(0, game->getScrnH() - (imgScale * 430));

    bfly = Butterfly(game->getRenderer(), "media/images/butterfly/butterfly.png", imgScale * 70,
                     imgScale * 70);
    bfly.setPos(0, /*game->getScrnW()*/ 100);

    blackbird = BlackBird(game->getRenderer(), "media/images/birds/black_bird.png", imgScale * 180,
                          imgScale * 120);
    blackbird.setPos(0, /*game->getScrnW()*/ 100);

    pinktree = PinkTree(game->getRenderer(), "media/images/trees/pink_tree.png",
                        (imgScale * 271) * 3, (imgScale * 240) * 3);
    pinktree.setPos(0, (game->getScrnH() - (imgScale * 240 * 3)));

    greentree = PinkTree(game->getRenderer(), "media/images/trees/green_tree.png",
                         (imgScale * 271) * 2.75f, (imgScale * 240) * 2.75f);
    greentree.setPos(game->getScrnW() - (((imgScale * 271) * 3.25f)),
                     (game->getScrnH() - (imgScale * 240 * 2.75f)));

    currPuzzle = Puzzle(game->getRenderer(), &grid, puzzles[puzzles_index]);

    btnPlay = Button(game->getRenderer(), "media/ui/play.png", grid.getCardwidth(),
                     grid.getCardheight());
    btnPlay.setPos(grid.getUpperpos2());

    btnquit = Button(game->getRenderer(), "media/ui/quit.png", imgScale * 128, imgScale * 128);
    SDL_Vector _pos325 = SDL_Vector(game->getScrnW() - (imgScale * 128), 0, 0);
    btnquit.setPos(_pos325);

    btninfo = Button(game->getRenderer(), "media/ui/info.png", imgScale * 128, imgScale * 128);
    SDL_Vector _pos335 = SDL_Vector(btnPlay.getPos().x + (btnPlay.getBtnRect()->w / 2),
                                    btnPlay.getPos().y + (btnPlay.getBtnRect()->h + 28), 0);
    btninfo.setPos(_pos335);

    if (bgTex.getTex() != NULL) {
        success = true;
    }

    eff_help = Mix_LoadWAV(currPuzzle.getPuzzleSound().c_str());
    eff_hello = Mix_LoadWAV("media/sounds/hello.ogg");
    eff_tools = Mix_LoadWAV("media/sounds/hello.ogg");
    eff_correct = Mix_LoadWAV("media/sounds/bing.ogg");
    eff_retry = Mix_LoadWAV("media/sounds/no.ogg");

    Mix_PlayChannel(-1, eff_hello, 0);

    for (int n = 0; n < AMOUNT; n++) {
        fire[n] = mFirework(game->getRenderer(), game->getScrnW(), game->getScrnH(), AMOUNT);
    }

    SDL_Color txtCol1 = {255, 255, 255, 0};

    return success;
}

/*implementation of global function declared in game.cpp*/
void handleTouchUps(float touchX, float touchY) {

}

/*implementation of global function declared in game.cpp*/
void handleTouchDwns(float touchX, float touchY) {
    SDL_Point touchLoc = {touchX, touchY,};
    switch (GAME_STATE) {
        case GAME_STATE_MENU:
            if (game->getTouchDwn()) {
                if (SDL_PointInRect(&touchLoc, btnPlay.getBtnRect())) {
                    GAME_STATE = GAME_STATE_LOADING;
                }

                if (SDL_PointInRect(&touchLoc, btninfo.getBtnRect())) {
                    GAME_STATE = GAME_STATE_CREDITS;
                }

                if (SDL_PointInRect(&touchLoc, btnquit.getBtnRect())) {
                    exit(EXIT_SUCCESS);
                }
            }
            break;

        case GAME_STATE_CREDITS:
            break;

        case GAME_STATE_LOADING:

            break;

        case GAME_STATE_EXITING:

            break;

        case GAME_STATE_3PUZZLE:
            if (game->getTouchDwn()) {
                processInput(touchLoc);

                if (SDL_PointInRect(&touchLoc, btnquit.getBtnRect())) {
                    GAME_STATE = GAME_STATE_EXITING;
                }

            }

            break;
        default:
            break;
    }

}

/*implementation of global function declared in game.cpp*/
void handleMouseInput(SDL_Event *event) {
    switch (GAME_STATE) {
        case GAME_STATE_MENU:
            switch (event->type) {

                case SDL_MOUSEBUTTONDOWN:

                    switch (event->button.button) {

                        case SDL_BUTTON_LEFT:
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            SDL_Point clickpoint = {x, y,};

                            if (SDL_PointInRect(&clickpoint, btnPlay.getBtnRect())) {
                                GAME_STATE = GAME_STATE_LOADING;
                            }

                            if (SDL_PointInRect(&clickpoint, btninfo.getBtnRect())) {
                                GAME_STATE = GAME_STATE_CREDITS;
                            }

                            break;

                    }

                    break;

                case SDL_MOUSEBUTTONUP:
                    switch (event->button.button) {
                        case SDL_BUTTON_LEFT:

                            break;
                    }
                    break;

            }

            break;

        case GAME_STATE_CREDITS:
            switch (event->type) {

                case SDL_MOUSEBUTTONDOWN:

                    switch (event->button.button) {

                        case SDL_BUTTON_LEFT:
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            SDL_Point clickpoint = {x, y,};

                            /*if (SDL_PointInRect(&clickpoint, btnquit.getBtnRect())) {
                                GAME_STATE = GAME_STATE_MENU;
                            }*/

                            break;

                    }

                    break;

                case SDL_MOUSEBUTTONUP:
                    switch (event->button.button) {
                        case SDL_BUTTON_LEFT:

                            break;
                    }
                    break;
            }
            break;

        case GAME_STATE_LOADING:

            break;

        case GAME_STATE_EXITING:

            break;

        case GAME_STATE_3PUZZLE:
            switch (event->type) {

                case SDL_MOUSEBUTTONDOWN:

                    switch (event->button.button) {

                        case SDL_BUTTON_LEFT:
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            SDL_Point clickpoint = {x, y,};

                            processInput(clickpoint);

                            if (SDL_PointInRect(&clickpoint, btnquit.getBtnRect())) {
                                GAME_STATE = GAME_STATE_EXITING;
                            }

                            break;

                    }

                    break;

                case SDL_MOUSEBUTTONUP:
                    switch (event->button.button) {
                        case SDL_BUTTON_LEFT:

                            break;
                    }
                    break;

            }

            break;
        default:
            break;
    }
}

/*implementation of global function declared in game.cpp*/
void handleInput(SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_AC_BACK:
                if (GAME_STATE == GAME_STATE_CREDITS) {
                    GAME_STATE = GAME_STATE_MENU;

                } else if (GAME_STATE == GAME_STATE_3PUZZLE) {
                    GAME_STATE = GAME_STATE_EXITING;

                } else if (GAME_STATE == GAME_STATE_MENU) {
                    //exit(0);
                }
                break;
        }
    }
}

void processInput(SDL_Point _point) {
    switch (GAME_STATE) {
        case GAME_STATE_MENU:

            break;

        case GAME_STATE_CREDITS:

            break;

        case GAME_STATE_LOADING:

            break;

        case GAME_STATE_3PUZZLE:
            if (SDL_PointInRect(&_point, currPuzzle.getLowerCard1().getTex()->getTexRect())) {
                clickCard.setPos(currPuzzle.getLowerCard1().getPos());

                if (currPuzzle.getSolution() == currPuzzle.getLowerCard1().getName()) {
                    updatePuzzle = true;
                    showFireworks = true;
                    Mix_PlayChannel(-1, eff_correct, 0);
                } else { Mix_PlayChannel(-1, eff_retry, 0); }

            } else if (SDL_PointInRect(&_point,
                                       currPuzzle.getLowerCard2().getTex()->getTexRect())) {
                clickCard.setPos(currPuzzle.getLowerCard2().getPos());

                if (currPuzzle.getSolution() == currPuzzle.getLowerCard2().getName()) {
                    updatePuzzle = true;
                    showFireworks = true;
                    Mix_PlayChannel(-1, eff_correct, 0);
                } else { Mix_PlayChannel(-1, eff_retry, 0); }

            } else if (SDL_PointInRect(&_point,
                                       currPuzzle.getLowerCard3().getTex()->getTexRect())) {
                clickCard.setPos(currPuzzle.getLowerCard3().getPos());

                if (currPuzzle.getSolution() == currPuzzle.getLowerCard3().getName()) {
                    updatePuzzle = true;
                    showFireworks = true;
                    Mix_PlayChannel(-1, eff_correct, 0);
                } else { Mix_PlayChannel(-1, eff_retry, 0); }

            }

            break;
        default:
            break;
    }

}
