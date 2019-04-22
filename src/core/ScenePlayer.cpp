#include "ScenePlayer.h"

#include "EventManager.h"
#include "GameObject.h"

#include <algorithm>

ScenePlayer* ScenePlayer::s_instance = nullptr;

ScenePlayer::ScenePlayer() {
    
}

void ScenePlayer::loadScene(ScenePlayer* scene) {
    s_instance = scene;
}

ScenePlayer& ScenePlayer::instance() {
	return *s_instance;
}

ScenePlayer::~ScenePlayer() {
	m_objects.clear();
}

void ScenePlayer::add(GameObject* obj) {
    obj->setId(++m_nextId);	
	m_createdObjects.push_back(std::shared_ptr<GameObject>(obj));
}

void ScenePlayer::destroy(GameObject* obj) {
	for (auto& it : m_destroyedObjectsIDs) {
		if (it == obj->getId()) {
			return;
		}			
	}
    m_destroyedObjectsIDs.push_back(obj->getId());
}

void ScenePlayer::setup() {
    onLoadScene();
}

void ScenePlayer::update(float dt) {
   
	//cria objetos--------------------------
	if (!m_createdObjects.empty()) {

		m_objects.insert(m_objects.end(), m_createdObjects.begin(), m_createdObjects.end());

		for (auto& it : m_createdObjects) {
			it->setup();
			EventManager::onObjectCreated(it);
		}
		m_createdObjects.clear();
	}	
	//-----------------------------------------

    //Destroi objetos-------------------------------
    if (!m_destroyedObjectsIDs.empty()) {
        for (int i = 0; i < m_destroyedObjectsIDs.size(); i++) {

            std::shared_ptr<GameObject> ptr(nullptr);
            int id = m_destroyedObjectsIDs[i];
            m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [id, &ptr](std::shared_ptr<GameObject> obj) {
                if (obj->getId() == id) {
                    ptr = obj;
                    return true;
                }
                return false;
            }));
            EventManager::onObjectDestroyed(ptr);
        }	
        m_destroyedObjectsIDs.clear();
    }
    //----------------------------------------------

    

	//atualiza objetos----------------------------	
	for (auto& it : m_objects) {
		it->update(dt);	
	}
	//--------------------------------------------	

    
}
