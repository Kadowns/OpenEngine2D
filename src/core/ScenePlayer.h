#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <set>
#include <unordered_set>

#include "Event.h"

class GameObject;

class ScenePlayer {
private:

	
	ScenePlayer(ScenePlayer&);
	ScenePlayer& operator = (ScenePlayer& other);

	std::vector<std::shared_ptr<GameObject>> m_objects, m_createdObjects;
    std::vector<size_t> m_destroyedObjectsIDs;
    static ScenePlayer* s_instance;
	static ScenePlayer* s_nextScene;
    size_t m_nextId = 0;

    virtual void onLoadScene() = 0;

protected:
    ScenePlayer();
	
public:

    static void loadScene(ScenePlayer* scene);
	static void showNextScene();

	static ScenePlayer& instance();
	static bool loadingScene;
	virtual ~ScenePlayer();

	void add(GameObject* obj);
	void destroy(GameObject* obj);

	template<typename T>
	std::vector<std::weak_ptr<T>> search();
    
	void update(float dt);
};

template<typename T>
inline std::vector<std::weak_ptr<T>> ScenePlayer::search() {
	std::vector<std::weak_ptr<T>> found;
	for (auto it : m_objects) {
		auto obj = dynamic_pointer_cast<T>(it);
		if (obj != nullptr) {
            std::weak_ptr<T> wk = obj;
            found.push_back(wk);
		}
	}
	return found;
}
