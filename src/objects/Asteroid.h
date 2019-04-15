#pragma once

#include "../core/Event.h"
#include "../core/GameObject.h"

class Sprite;
class Rigidbody2D;
class Collider;


class Asteroid : public GameObject {
public:
    enum ASTEROID_TYPE {
        BIG = 0,
        SMALL = 1
    };

    Asteroid(const ofVec2f& position, const ofVec2f& initialVelocity, float initialAngularVelocity, ASTEROID_TYPE type);
    ~Asteroid();

    void onCollisionWith(GameObject* other);
    void applyDamage(ofVec2f direction);
    void destroy();

private:

    Event<GameObject*>::EventListener m_onCollisionWithCallback;

    ASTEROID_TYPE m_type; 
    Sprite* m_sprite;
    Rigidbody2D* m_rb;
    Collider* m_collider;

    int m_hitPoints;


    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;

};
