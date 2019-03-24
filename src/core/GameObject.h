#pragma once
#include "Transform2D.h"

class GameObject {
public:
	
    Transform2D transform;

	virtual void setup() = 0;
	virtual void update(float dt) = 0;

	virtual ~GameObject() = default;
};

