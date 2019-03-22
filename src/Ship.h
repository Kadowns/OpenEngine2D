#pragma once
#include <ofImage.h>

#include "Collider.h"
#include "Team.h"
#include "GameObject.h"
#include "ofVectorMath.h"

class Ship : public GameObject, public Team {
private:

	ofImage* m_image;
	Collider m_collider;
	ofVec2f m_position;	
	float m_rotation = 0;	
	float m_speed = 450.0f;
	float m_fireDelay = 0.5f;
	float m_lastFire = 0;

	std::string m_playerNumber;

public:
	Ship(const int& playerNumber, const ofVec2f& position, TEAM team);
	~Ship();

	// Inherited via GameObject
	virtual void setup() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

