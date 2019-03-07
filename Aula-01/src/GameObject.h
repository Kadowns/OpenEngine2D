#pragma once
class GameObject {

public:
	
	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual bool isAlive() = 0;

	virtual ~GameObject() = default;
};

