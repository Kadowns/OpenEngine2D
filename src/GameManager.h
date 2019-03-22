#pragma once

#include <vector>
#include <queue>


#include "ofGraphics.h"

#include "GameObject.h"
#include "Collider.h"
#include "Event.h"

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

	template<typename T>
	std::vector<T*> search();

	void setup();
	void update();
	void draw();

};

template<typename T>
inline std::vector<T*> GameManager::search() {
	std::vector<T*> found;
	for (auto it : m_objects) {
		auto obj = dynamic_cast<T*>(it);
		if (obj != nullptr) {
            found.push_back(obj);
		}
	}
	return found;
}
