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

double GameManager::elapsedTime() {
	return ofGetElapsedTimef() - m_elapsedTime;
}

void GameManager::setup() {
	for (auto& it : m_objects) {
		it->setup();
	}
}

void GameManager::update() {
		
	for (auto& it : m_objects) {
		it->update();
	}
	m_elapsedTime = ofGetElapsedTimef();
}

void GameManager::draw() {
	for (auto& it : m_objects) {
		it->draw();
	}
}
