#pragma once

#include "GameObject.h"
#include "ofVectorMath.h"
#include "ofImage.h"

class Bullet : public GameObject {
private:

	ofImage* m_image;
	ofRectangle m_collider;
	ofVec2f m_position;
	float m_rotation;
	float m_speed = 600.0f;	

public:
	Bullet(const ofVec2f& position, const float& rotation);
	~Bullet();

	// Inherited via GameObject
	virtual void setup() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

