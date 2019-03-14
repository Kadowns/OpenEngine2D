#pragma once
#include <ofImage.h>

#include "GameObject.h"
#include "ofVectorMath.h"

class Ship : public GameObject {
private:

	ofImage* m_image;
	ofRectangle m_collider;
	ofVec2f m_position;	
	float m_rotation = 0;	
	float m_speed = 450.0f;
	float m_fireDelay = 0.5f;
	float m_lastFire = 0;
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	virtual void setup() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

