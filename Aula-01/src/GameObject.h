#pragma once

class GameObject {

public:
	
	virtual void setup() = 0;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual void onCollisionWith(GameObject*) { printf("bateu!"); }

	virtual ~GameObject() = default;
};

