#include "Ship.h"

#include "DataLoader.h"
#include "GameManager.h"
#include "Input.h"
#include "ofGraphics.h"

#include "Bullet.h"

Ship::Ship(const int& playerNumber, const ofVec2f& position, TEAM team) {
	m_image = DataLoader::instance().getImage("ship");
	m_team = team;
	m_collider.first = this;
	m_collider.second = new ofRectangle(
		m_position,
		m_image->getWidth(),
		m_image->getHeight()
	);
	m_position = position;

	m_playerNumber = std::to_string(playerNumber);
}

Ship::~Ship() {
	GameManager::instance().unsubscribeFromCollision(&m_collider);
}

ofVec2f Ship::getPosition() {
    return m_position;
}

void Ship::setup() {
	GameManager::instance().subscribeToCollision(&m_collider);
}

void Ship::update(float dt) {

	if (Input::getButtonDown("turnright" + m_playerNumber)) {
		m_rotation += ofDegToRad(360) * dt;
	}
	if (Input::getButtonDown("turnleft" + m_playerNumber)) {
		m_rotation -= ofDegToRad(360) * dt;
	}	

	if (Input::getButtonDown("moveup" + m_playerNumber)) {
		m_position += ofVec2f(cos(m_rotation), sin(m_rotation)) * m_speed * dt;
	}
	if (Input::getButtonDown("movedown" + m_playerNumber)) {
		m_position -= ofVec2f(cos(m_rotation), sin(m_rotation)) * m_speed * dt;
	}

	m_lastFire += dt;
	if (Input::getButtonDown("fire" + m_playerNumber) && m_lastFire > m_fireDelay) {
		GameManager::instance().add(new Bullet(m_position, m_rotation, m_team));
		m_lastFire = 0;
	}

	m_collider.second->position = m_position;	
}

void Ship::draw() {
	ofPushMatrix();
	ofTranslate(m_position);
	ofRotateZ(ofRadToDeg(m_rotation) + 90);
	m_image->draw(0,0);
	ofPopMatrix();
}
