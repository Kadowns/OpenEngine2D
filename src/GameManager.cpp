#include "GameManager.h"
#include "ofMain.h"

#include "Ship.h"

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

void GameManager::subscribeToCollision(Collider* col) {
	m_colliders.push_back(col);
}

void GameManager::unsubscribeFromCollision(Collider* col) {
	m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), col));
}

void GameManager::setup() {
	add(new Ship(0, ofVec2f(300, 500), TEAM_RED));
	add(new Ship(1, ofVec2f(600, 500), TEAM_BLUE));
}

void GameManager::update() {

	//cria objetos--------------------------
	while (!m_createdObjects.empty()) {
		auto obj = m_createdObjects.front();
		obj->setup();
		m_objects.push_back(obj);
		m_createdObjects.pop();
	}
	//-----------------------------------------


	//atualiza objetos----------------------------
	auto dt = ofGetLastFrameTime();
	for (auto& it : m_objects) {
		it->update(dt);	
	}
	//--------------------------------------------

	//testa colisões---------------------------------
	for (int i = 0; i < m_colliders.size(); i++) {
		for (int j = 0; j < m_colliders.size(); j++) {
			if (i <= j) {
				continue;
			}

			if (m_colliders[i]->second->intersects(*m_colliders[j]->second)) {
				m_colliders[i]->first->onCollisionWith(m_colliders[j]->first);
				m_colliders[j]->first->onCollisionWith(m_colliders[i]->first);
			}
		}
	}
	//-----------------------------------------------

	//Destroi objetos-------------------------------
	while (!m_destroyedObjects.empty()) {
		auto obj = m_destroyedObjects.front();
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), obj));
		delete obj;
		m_destroyedObjects.pop();
	}
	//----------------------------------------------
}

void GameManager::draw() {
	for (auto& it : m_objects) {
		it->draw();
	}
}
