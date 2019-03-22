#pragma once

#include <map>

#include "ofGraphics.h"
#include "../Event.h"

class GameObject;
class ofRectangle;
class ofVec2f;

class Collider {

public:
    Event<GameObject*> onCollisionWith;

    Collider(GameObject* pAttached, ofVec2f* pPosition, float w, float h);
    ~Collider();

    void tryCollision(Collider& other);
    

    GameObject* getAttachedGameObject();
    const ofRectangle& getRectangle();

private:

    Collider(Collider&);
    Collider& operator = (Collider& other);

    void updatePosition();

    GameObject* p_attached;
    ofVec2f* p_position;
    ofRectangle m_rec;

};
