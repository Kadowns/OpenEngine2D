#include "GameManager.h"

#include "../objects/Ship.h"
#include "../objects/Asteroid.h"
#include "../objects/CameraController.h"
#include "../objects/StarBackground.h"

GameManager::GameManager() {
    
}


GameManager& GameManager::instance() {
	static GameManager s_instance;
	return s_instance;
}

GameManager::~GameManager() {
	for (auto& it : m_objects) {
		delete it;
	}
}

void GameManager::add(GameObject* obj) {
    obj->setId(++m_nextId);
	m_createdObjects.push_back(obj);
}

void GameManager::destroy(GameObject* obj) {
    //gambiarra? um objeto não pode ser destruido mais de uma vez
    for (auto it : m_destroyedObjects) {
        if (it->getId() == obj->getId()) {
            return;
        }
    }
	m_destroyedObjects.push_back(obj);
}

void GameManager::setup() {    
	add(new Ship(0, ofVec2f(0, 0), TEAM_RED));
	//add(new Ship(1, ofVec2f(600, 500), TEAM_BLUE));
    add(new CameraController());
    add(new StarBackground(200));
    add(new Asteroid(ofVec2f(300, 300), ofVec2f(ofRandom(-500, 500), ofRandom(-500, 500)), ofRandom(-180, 180), Asteroid::BIG));
   
}

void GameManager::update(float dt) {
   
    //Destroi objetos-------------------------------
    while (!m_destroyedObjects.empty()) {
        auto obj = m_destroyedObjects.back();
        m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), obj));
        delete obj;
        m_destroyedObjects.pop_back();
    }
    //----------------------------------------------

    //cria objetos--------------------------
    while (!m_createdObjects.empty()) {
        auto obj = m_createdObjects.back();
        obj->setup();
        m_objects.push_back(obj);
        m_createdObjects.pop_back();
    }
    //-----------------------------------------

	//atualiza objetos----------------------------	
	for (auto& it : m_objects) {
		it->update(dt);	
	}
	//--------------------------------------------	

    
}
