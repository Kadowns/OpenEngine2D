#include "GameManager.h"

#include "EventManager.h"

#include "../objects/Ship.h"
#include "../objects/Asteroid.h"
#include "../objects/AsteroidManager.h"
#include "../objects/CameraController.h"
#include "../objects/StarBackground.h"
#include "../objects/DebugSquare.h"

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
	m_objects.clear();
}

void GameManager::add(GameObject* obj) {
    obj->setId(++m_nextId);	
	m_createdObjects.push_back(obj);	
}

void GameManager::destroy(GameObject* obj) {
	for (auto& it : m_destroyedObjects) {
		if (it->getId() == obj->getId()) {
			printf("Objeto com id repetida:%d\n", obj->getId());
			return;
		}			
	}
	printf("Objeto com id adicionado para destruicao:%d\n", obj->getId());
	m_destroyedObjects.push_back(obj);
}

void GameManager::setup() {
	add(new Ship(0, ofVec2f(400, 400), TEAM_RED));
	//add(new Ship(1, ofVec2f(600, 500), TEAM_BLUE));
	add(new CameraController());
	add(new StarBackground(200));
	add(new DebugSquare());
	add(new AsteroidManager(2));
}

void GameManager::update(float dt) {
   
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
    while (!m_destroyedObjects.empty()) {		
		auto obj = m_destroyedObjects.front();
        m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), obj));        
		m_destroyedObjects.erase(std::remove(m_destroyedObjects.begin(), m_destroyedObjects.end(), obj));
		delete obj;
		EventManager::onObjectDestroyed(obj);
    }
    //----------------------------------------------

    

	//atualiza objetos----------------------------	
	for (auto& it : m_objects) {
		it->update(dt);	
	}
	//--------------------------------------------	

    
}
