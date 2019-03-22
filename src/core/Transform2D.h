#pragma once
#include "ofGraphics.h"

struct Transform2D {

    ofVec2f position;
    float scale = 1;
    float rotation = 0;

    ofVec2f getRight();
    ofVec2f getUp();   
};
