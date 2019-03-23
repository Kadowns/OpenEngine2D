#pragma once


#include "../core/GameObject.h"

#include "Team.h"

class Sprite;
class Collider;

class Ship : public GameObject, public Team {
private:

	Sprite* m_sprite;
	Collider* m_collider;		
	float m_speed = 450.0f;
	float m_fireDelay = 0.15f;
	float m_lastFire = 0;
	
    std::string m_buttonRight, m_buttonLeft, m_buttonForward, m_buttonBackward, m_buttonFire;

public:
	Ship(const int& playerNumber, const ofVec2f& position, TEAM team);
	~Ship();

	// Inherited via GameObject
	virtual void setup() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

