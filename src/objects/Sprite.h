#pragma once

#include "ofImage.h"

class GameObject;

class Sprite {
public:

    Sprite(GameObject* attached, const char* imageName);
    ~Sprite();

    void draw();

    float getWidth();
    float getHeight();


private:

    GameObject* m_attached;
    ofImage* m_image;

};
