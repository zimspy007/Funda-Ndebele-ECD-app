#include "particle.hpp"

FireworkParticle::FireworkParticle() {

}

FireworkParticle::~FireworkParticle() {

}

void FireworkParticle::moveParticle(int r) {
    this->dist++;
    this->intensity = 255 - (this->dist * 255 / r);
    if (this->intensity <= 0) {
        this->intensity = 0;
    }
}

void FireworkParticle::setDist(int dist) {
    this->dist = dist;
}

void FireworkParticle::setSize(int size) {
    this->size = size;
}

void FireworkParticle::setIntensity(int intensity) {
    this->intensity = intensity;
}

void FireworkParticle::setAngle(int angle) {
    this->angle = angle;
}

int FireworkParticle::getDist() {
    return this->dist;
}

int FireworkParticle::getSize() {
    return this->size;
}

int FireworkParticle::getIntensity() {
    return this->intensity;
}

int FireworkParticle::getAngle() {
    return this->angle;
}