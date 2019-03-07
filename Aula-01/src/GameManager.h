#pragma once

#include <vector>

#include "GameObject.h"

class GameManager {
private:

	GameManager();
	GameManager(GameManager&);
	GameManager& operator = (GameManager& other);

	std::vector<GameObject*> m_objects;

	double m_elapsedTime = 0;

public:

	static GameManager& instance();
	~GameManager();

	double elapsedTime();
	void setup();
	void update();
	void draw();

};

