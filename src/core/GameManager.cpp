#include "GameManager.h"

#include "../objects/Ship.h"
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
	m_createdObjects.push(obj);
}

void GameManager::destroy(GameObject* obj) {
	m_destroyedObjects.push(obj);
}

void GameManager::setup() {    
	add(new Ship(0, ofVec2f(0, 0), TEAM_RED));
	add(new Ship(1, ofVec2f(600, 500), TEAM_BLUE));
    add(new CameraController());
    add(new StarBackground(200));
}

void GameManager::update(float dt) {

	//cria objetos--------------------------
	while (!m_createdObjects.empty()) {
		auto obj = m_createdObjects.front();
		obj->setup();
		m_objects.push_back(obj);
		m_createdObjects.pop();
	}
	//-----------------------------------------

    //Destroi objetos-------------------------------
    while (!m_destroyedObjects.empty()) {
        auto obj = m_destroyedObjects.front();
        m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), obj));
        delete obj;
        m_destroyedObjects.pop();
    }
    //----------------------------------------------

	//atualiza objetos----------------------------
	
	for (auto& it : m_objects) {
		it->update(dt);	
	}
	//--------------------------------------------	
}
