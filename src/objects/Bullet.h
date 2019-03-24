#pragma once

#include "../Event.h"

#include "../core/GameObject.h"

#include "Team.h"

class Collider;
class Sprite;
class Rigidbody2D;

class Bullet : public GameObject, public Team {
private:
	
	Collider* m_collider;
    Sprite* m_sprite;
    Rigidbody2D* m_rb;
	float m_speed = 10.0f, m_targetRotation;	

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

