#include "GameManager.h"
#include "ofMain.h"

#include "Ship.h"

GameManager::GameManager() {
	m_objects.push_back(new Ship());
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
	for (auto& it : m_objects) {
		it->setup();
	}
}

void GameManager::update() {

	
	while (!m_createdObjects.empty()) {
		auto obj = m_createdObjects.front();
		obj->setup();
		m_objects.push_back(obj);
		m_createdObjects.pop();
	}
	
	auto dt = ofGetLastFrameTime();
	for (auto& it : m_objects) {
		it->update(dt);	
	}

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

	while (!m_destroyedObjects.empty()) {
		auto obj = m_destroyedObjects.front();
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), obj));
		m_destroyedObjects.pop();
	}
}

void GameManager::draw() {
	for (auto& it : m_objects) {
		it->draw();
	}
}
