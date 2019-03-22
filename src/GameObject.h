#pragma once
#include <stdlib.h>
#include <stdio.h>

class GameObject {
private :
	int numCollisions = 0;

public:
	
	virtual void setup() = 0;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual void onCollisionWith(GameObject*) {
		numCollisions++;
		printf("bateu! numero de batidas: %d\n", numCollisions);
	}

	virtual ~GameObject() = default;
};

