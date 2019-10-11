#ifndef _FPARTICLE_HPP_
#define _FPARTICLE_HPP_

class FireworkParticle {
public :

    FireworkParticle();

    ~FireworkParticle();

    void moveParticle(int r);

    void setDist(int dist);

    void setSize(int size);

    void setIntensity(int intensity);

    void setAngle(int angle);

    int getDist();

    int getSize();

    int getIntensity();

    int getAngle();

private:

    int dist;
    int size;
    int intensity;
    float angle;
};

#endif