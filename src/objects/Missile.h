#pragma once

#include "../Event.h"
#include "../core/GameObject.h"
#include "Team.h"

class Ship;
class Collider;
class Sprite;

class Missile : public GameObject, public Team {
public:

    Missile(const ofVec2f& position, const float& rotation, TEAM team);
    ~Missile();

    void onCollisionWith(GameObject* go);

private:

    Collider* m_collider;
    Sprite* m_sprite;
    float m_speed = 6000.0f;

    Ship* m_target = nullptr;

    //callbacks
    Event<GameObject*>::EventListener m_onCollisionCallback;


    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;
};
