#pragma once

#include <vector>
#include <queue>


#include "GameObject.h"
#include "Event.h"

typedef std::pair<GameObject*, ofRectangle*> Collider;

class GameManager {
private:

	GameManager();
	GameManager(GameManager&);
	GameManager& operator = (GameManager& other);

	std::vector<GameObject*> m_objects;
	std::queue<GameObject*> m_createdObjects, m_destroyedObjects;

	std::vector<Collider*> m_colliders;
	double m_elapsedTime = 0;

public:

	static GameManager& instance();
	~GameManager();

	void add(GameObject* obj);
	void destroy(GameObject* obj);
	void subscribeToCollision(Collider*);
	void unsubscribeFromCollision(Collider*);
	void setup();
	void update();
	void draw();

};

