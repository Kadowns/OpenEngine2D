#include "EventManager.h"

Event<int, int, int> EventManager::onMousePressed;
Event<int, int, int> EventManager::onMouseReleased;
Event<int, int> EventManager::onMouseMove;
Event<int, int> EventManager::onWindowResized;