#include "camera.hpp"

Camera::Camera() {

}

Camera::Camera(int w, int h) :
        w(w), h(h) {

    camRect = {x, y, w, h};

}

int Camera::getH() {
    return this->h;
}

int Camera::getW() {
    return this->w;
}

Camera::~Camera() {

}
