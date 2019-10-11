#include "game.hpp"

extern void drawGame();

extern void updateGame(float deltaTime);

extern void handleTouchUps(float touchX, float touchY);

extern void handleTouchDwns(float touchX, float touchY);

extern void handleMouseInput(SDL_Event *event);

extern void handleInput(SDL_Event *event);

Game::Game() {
    Game::initAll();
}

Game::~Game() {

}

/*functions*/
bool Game::initAll() {
    bool result = false;

    SDL_Init(SDL_INIT_EVERYTHING);

    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) < 0) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_VERBOSE, "SDL Init", "SDL failed to init");
#endif
        exit(2);
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_VERBOSE,
                            "SDL_image could not initialize! SDL_image Error: %s\n",
                            IMG_GetError());
#endif
        exit(2);
    }

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    //SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    result = true;
    return result;
}

void Game::runGame() {
    float dt = PHYSICS_TIMESTEP;
    Uint64 currentTime = SDL_GetPerformanceCounter();
    float accumulator = 0;

    while (!done) {

        const Uint64 newTime = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(newTime - currentTime) /
                          SDL_GetPerformanceFrequency(); //aka time for this frame
        currentTime = newTime;

        if (deltaTime > 0.25f)
            deltaTime = 0.25f; // anti "spiral of death" / breakpoints

        accumulator += deltaTime;

        while (accumulator >= dt) {
            accumulator -= dt;
            Game::updateGame(deltaTime);
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        Game::drawGame();

        /* Update the screen! */
        SDL_RenderPresent(renderer);
    }
}

void Game::drawGame() {
    ::drawGame();

    //draw fixed content
}

void Game::handleAllEvents() {
    SDL_Point touchLocation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

    /* Check for events */
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = 1;

        } //Touch down
        else if (event.type == SDL_FINGERDOWN) {
            touchLocation.x = event.tfinger.x * SCREEN_WIDTH;
            touchLocation.y = event.tfinger.y * SCREEN_HEIGHT;
            touchDwn = true;
            touchUp = false;
            touchSwipe = false;
            ::handleTouchDwns(touchLocation.x, touchLocation.y);

        }
            //Touch motion
        else if (event.type == SDL_FINGERMOTION) {
            touchLocation.x = event.tfinger.x * SCREEN_WIDTH;
            touchLocation.y = event.tfinger.y * SCREEN_HEIGHT;
            touchSwipe = true;
            touchUp = false;
            touchDwn = false;
        }
            //Touch up
        else if (event.type == SDL_FINGERUP) {
            touchLocation.x = event.tfinger.x * SCREEN_WIDTH;
            touchLocation.y = event.tfinger.y * SCREEN_HEIGHT;
            touchUp = true;
            touchDwn = false;
            touchSwipe = false;
            ::handleTouchUps(touchLocation.x, touchLocation.y);
        } else if (event.type == SDL_KEYDOWN) {
            //keyboard if needed
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    pEsc = true;
                    break;

                default:
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            //Select surfaces based on key press
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    pEsc = false;
                    break;

                default:
                    break;
            }
        }
    }
    ::handleMouseInput(&event);
    if (pEsc)
        done = 1;
}

void Game::updateGame(float deltaTime) {
    Game::handleAllEvents();
    ::handleInput(&event);

    ::updateGame(deltaTime);
}

void Game::shutdown() {
    SDL_DestroyRenderer(this->renderer);
    this->renderer = NULL;

    SDL_DestroyWindow(this->window);
    this->window = NULL;

    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

bool Game::getTouchUp() {
    return this->touchUp;
}

bool Game::getTouchDwn() {
    return this->touchDwn;
}

bool Game::getPEsc() {
    return this->pEsc;
}

bool Game::getTouchSwipe() {
    return this->touchSwipe;
}

int Game::getScrnW() {
    return this->SCREEN_WIDTH;
}

int Game::getScrnH() {
    return this->SCREEN_HEIGHT;
}

SDL_Renderer *Game::getRenderer() {
    return this->renderer;
}

SDL_Window *Game::getWindow() {
    return this->window;
}

SDL_Event *Game::getEvent() {
    return &this->event;
}