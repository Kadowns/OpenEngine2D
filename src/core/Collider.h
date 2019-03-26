#pragma once

#include <map>

#include "ofGraphics.h"

#include "Event.h"

class GameObject;
struct Transform2D;
class Rigidbody2D;

class Collider {

public:
    Event<GameObject*> onCollisionWith;

    Collider(GameObject* pAttached, Transform2D* pTransform, Rigidbody2D* rb);
    virtual ~Collider();

    virtual void tryCollision(Collider* other) = 0;

    GameObject* getGameObject();

protected:

    Collider(Collider&);
    Collider& operator = (Collider& other);

    GameObject* p_gameObject;
    Transform2D* p_transform;
    Rigidbody2D* p_rb;

};
