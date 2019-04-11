#pragma once

#include "../core/GameObject.h"
#include "../core/EventManager.h"

class Ship;

class AsteroidManager : public GameObject {

public:

	AsteroidManager(float spawnInterval);
	~AsteroidManager();

	void onWindowResized(int x, int y);

private:


	Ship* m_target = nullptr;

	ofVec2f m_windowSize;

	float m_timeToSpawn = 8, m_timeToNextSpawn;

	Event<int, int>::EventListener m_onWindowResizeCallback;

	void spawnAsteroid();

	// Inherited via GameObject
	virtual void setup() override;
	virtual void update(float dt) override;
};
