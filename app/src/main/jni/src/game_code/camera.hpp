#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL.h>

class Camera {
public:
    Camera();

    Camera(int w, int h);

    ~Camera();

    SDL_Rect camRect;

    int getH();

    int getW();

private:
    int w;
    int h;
    int x = 0;
    int y = 0;

};

#endif
