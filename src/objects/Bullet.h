#pragma once

#include "../core/Event.h"
#include "../core/GameObject.h"

#include "Team.h"

class Collider;
class Sprite;

class Bullet : public GameObject, public Team {
private:
	
	Collider* m_collider;
    Sprite* m_sprite;
    float m_speed = 800.0f, m_targetRotation, m_lifetime = 4, m_timealive = 0;

    //callbacks
    Event<GameObject*>::EventListener m_onCollisionCallback;

public:
	Bullet(const ofVec2f& position, const float& rotation, TEAM team);
	~Bullet();

	// Inherited via GameObject
    void onCollisionWith(GameObject*);
	virtual void setup() override;
	virtual void update(float dt) override;
};

