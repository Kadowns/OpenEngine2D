#include "Transform2D.h"

ofVec2f Transform2D::getRight() {    
    return ofVec2f(cos(rotation), sin(rotation));
}

ofVec2f Transform2D::getUp() {
    auto right = getRight();
    return ofVec2f(right.y, -right.x);
}
