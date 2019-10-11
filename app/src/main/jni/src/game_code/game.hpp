#ifndef GAME_BASE_HPP
#define GAME_BASE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#ifdef __ANDROID__

#include <android/log.h>

#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "gtexture.hpp"
#include "camera.hpp"

#define PHYSICS_TIMESTEP 0.01f

class Game {
public:
    Game();

    ~Game();

    bool initAll();

    void runGame();

    void drawGame();

    void handleAllEvents();

    void updateGame(float deltaTime);

    void shutdown();

    bool getTouchUp();

    bool getTouchDwn();

    bool getTouchSwipe();

    bool getPEsc();

    int getScrnW();

    int getScrnH();

    SDL_Renderer *getRenderer();

    SDL_Window *getWindow();

    SDL_Event *getEvent();

private:

    bool touchUp = false;
    bool touchDwn = false;
    bool touchSwipe = false;
    bool pEsc = false;

    int SCREEN_WIDTH = 960, SCREEN_HEIGHT = 540;

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Event event;
    Uint8 done = 0;
};

#endif
