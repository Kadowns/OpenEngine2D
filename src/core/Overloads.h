#pragma once

#include "ofMath.h"
#include <ofVectorMath.h>


#define DEBUG_VEC(vec) printf("x:%f y:%f\n", vec.x, vec.y)

inline ofVec2f lerp(const ofVec2f& first, const ofVec2f& second, float percent) {
    return ofVec2f(ofLerp(first.x, second.x, percent), ofLerp(first.y, second.y, percent));
}

inline ofColor lerp(const ofColor& first, const ofColor& second, float percent) {
    float invAmount = 1.f - percent;
    return ofColor(
        invAmount * first.r + percent * second.r,
        invAmount * first.g + percent * second.g,
        invAmount * first.b + percent * second.b,
        invAmount * first.a + percent * second.a
    );
}