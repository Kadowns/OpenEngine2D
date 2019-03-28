#pragma once

#include "ofVectorMath.h"

#include "Event.h"

class EventManager {

public:

    static Event<int, int> onMousePressed;
    static Event<int, int> onMouseReleased;
    static Event<int, int> onMouseMove;
    static Event<int, int> onMouseDragged;
    static Event<int, int, float, float> onMouseScrolled;
    static Event<int, int> onWindowResized;

};
