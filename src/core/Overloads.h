#pragma once

#include "ofMath.h"
#include <ofVectorMath.h>


inline ofVec2f lerp(const ofVec2f& first, const ofVec2f& second, float percent) {
    return ofVec2f(ofLerp(first.x, second.x, percent), ofLerp(first.y, second.y, percent));
}