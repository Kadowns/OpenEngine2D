#include "Ship.h"

#include "DataLoader.h"
#include "GameManager.h"

Ship::Ship() {
	m_image = DataLoader::instance().getImage("ship");
}

Ship::~Ship() {
}

void Ship::setup() {
}

void Ship::update() {
	if (ofGetKeyPressed(OF_KEY_RIGHT)) {
		position.x += speed * GameManager::instance().elapsedTime();
	}
	if (ofGetKeyPressed(OF_KEY_LEFT)) {
		position.x -= speed * GameManager::instance().elapsedTime();
	}
}

void Ship::draw() {
	m_image->draw(position);
}

bool Ship::isAlive() {
	return false;
}
