#pragma once

#include "ofVectorMath.h"

#include "../Event.h"

class EventManager {

public:

    static Event<int, int, int> onMousePressed;
    static Event<int, int, int> onMouseReleased;
    static Event<int, int> onMouseMove;
    static Event<int, int> onWindowResized;

};
