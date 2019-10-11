#include "firework.hpp"

mFirework::mFirework() {

}

mFirework::mFirework(SDL_Renderer *renderer, int w, int h, int amnt) {
    srand(time(NULL));

    this->amount = amnt;

    SDL_Surface *blackSurface = SDL_LoadBMP("media/fireworks/black.bmp");
    SDL_Surface *circleSurface1 = SDL_LoadBMP("media/fireworks/circle1.bmp");
    SDL_Surface *circleSurface2 = SDL_LoadBMP("media/fireworks/circle2.bmp");
    SDL_Surface *circleSurface3 = SDL_LoadBMP("media/fireworks/circle3.bmp");
    SDL_Surface *circleSurface4 = SDL_LoadBMP("media/fireworks/circle4.bmp");
    SDL_Surface *circleSurface5 = SDL_LoadBMP("media/fireworks/circle5.bmp");
    SDL_Surface *circleSurface6 = SDL_LoadBMP("media/fireworks/circle6.bmp");

    SDL_SetColorKey(circleSurface1, SDL_TRUE, SDL_MapRGB(circleSurface1->format, 195, 195, 195));
    SDL_SetColorKey(circleSurface2, SDL_TRUE, SDL_MapRGB(circleSurface2->format, 195, 195, 195));
    SDL_SetColorKey(circleSurface3, SDL_TRUE, SDL_MapRGB(circleSurface3->format, 195, 195, 195));
    SDL_SetColorKey(circleSurface4, SDL_TRUE, SDL_MapRGB(circleSurface4->format, 195, 195, 195));
    SDL_SetColorKey(circleSurface5, SDL_TRUE, SDL_MapRGB(circleSurface5->format, 195, 195, 195));
    SDL_SetColorKey(circleSurface6, SDL_TRUE, SDL_MapRGB(circleSurface6->format, 195, 195, 195));

    circles[0] = SDL_CreateTextureFromSurface(renderer, circleSurface6);
    circles[1] = SDL_CreateTextureFromSurface(renderer, circleSurface1);
    circles[2] = SDL_CreateTextureFromSurface(renderer, circleSurface2);
    circles[3] = SDL_CreateTextureFromSurface(renderer, circleSurface3);
    circles[4] = SDL_CreateTextureFromSurface(renderer, circleSurface4);
    circles[5] = SDL_CreateTextureFromSurface(renderer, circleSurface5);

    int i;
    for (i = 0; i < 6; i++) {
        SDL_SetTextureBlendMode(circles[i], SDL_BLENDMODE_BLEND);
    }

    SDL_Rect rectWindow;
    rectWindow.x = 0;
    rectWindow.y = 0;
    rectWindow.h = w;
    rectWindow.w = h;

    for (i = 0; i < amnt; i++) {
        initFirework(w, h);
    }
}

void mFirework::initFirework(int w, int h) {
    this->cX = rand() % w;
    this->cY = rand() % h;
    this->r = rand() % 80 + 50;
    this->amount = rand() % 11 + 10;
    this->circle = circles[rand() % 6];

    int i;
    for (i = 0; i < this->amount; i++) {
        this->particle[i].setDist(0);
        this->particle[i].setSize(7);
        this->particle[i].setAngle(i * 2 * PI / this->amount);
        this->particle[i].setIntensity(255);
    }
}

void mFirework::updateFirework() {
    int i;
    for (i = 0; i < this->amount; i++) {
        this->particle[i].moveParticle(this->r);
    }
    if (this->particle[0].getIntensity() == 0) {
        initFirework(960, 540);
    }
}

void mFirework::sketchFirework(SDL_Renderer *renderer, SDL_Rect *rect) {

    int i;
    for (i = 0; i < this->amount; i++) {
        FireworkParticle *particle = &(this->particle[i]);
        int d = particle->getDist();
        rectCircle.x = (int) (d * cos(particle->getAngle()) + this->cX);
        rectCircle.y = (int) (d * sin(particle->getAngle()) + this->cY);
        rectCircle.h = particle->getSize();
        rectCircle.w = particle->getSize();

        SDL_SetTextureAlphaMod(this->circle, particle->getIntensity());
        SDL_RenderCopy(renderer, this->circle, NULL, &rectCircle);
    }
}

void mFirework::destroyFirework() {
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(circles[i]);
    }
}

mFirework::~mFirework() {

}