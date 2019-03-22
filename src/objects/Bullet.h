#pragma once

#include "../Event.h"

#include "GameObject.h"
#include "Team.h"

class Ship;
class Collider;
class Sprite;

class Bullet : public GameObject, public Team {
private:
	
	Collider* m_collider;
    Sprite* m_sprite;
	float m_speed = 600.0f;	

    Ship* m_target = nullptr;


    //callbacks
    Event<GameObject*>::EventListener m_onCollisionCallback;

public:
	Bullet(const ofVec2f& position, const float& rotation, TEAM team);
	~Bullet();

	// Inherited via GameObject
    void onCollisionWith(GameObject*);
	virtual void setup() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

