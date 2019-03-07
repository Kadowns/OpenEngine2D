#pragma once
#include <ofImage.h>

#include "GameObject.h"
#include "ofVectorMath.h"

class Ship : public GameObject {
private:

	ofImage* m_image;
	ofVec2f position;
	float speed = 30.0f;
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;
	virtual bool isAlive() override;
};

