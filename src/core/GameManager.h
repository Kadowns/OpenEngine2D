#pragma once

#include <vector>
#include <queue>

#include "Event.h"
#include "Camera.h"

class GameObject;

class GameManager {
private:

	GameManager();
	GameManager(GameManager&);
	GameManager& operator = (GameManager& other);

	std::vector<GameObject*> m_objects;
	std::queue<GameObject*> m_createdObjects, m_destroyedObjects;
	

public:

	static GameManager& instance();
	~GameManager();

	void add(GameObject* obj);
	void destroy(GameObject* obj);

	template<typename T>
	std::vector<T*> search();
    
	void setup();
	void update(float dt);

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
