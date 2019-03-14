#include "Ship.h"

#include "DataLoader.h"
#include "GameManager.h"
#include "ofGraphics.h"

#include "Bullet.h"

Ship::Ship() {
	m_image = DataLoader::instance().getImage("ship");
}

Ship::~Ship() {
	GameManager::instance().subscribeToCollision(new Collider(dynamic_cast<GameObject*>(this), &m_collider));
}

void Ship::setup() {
	GameManager::instance().subscribeToCollision(new Collider(dynamic_cast<GameObject*>(this), &m_collider));
}

void Ship::update(float dt) {

	if (ofGetKeyPressed(OF_KEY_RIGHT)) {		
		m_rotation += ofDegToRad(360) * dt;
	}
	if (ofGetKeyPressed(OF_KEY_LEFT)) {
		m_rotation -= ofDegToRad(360) * dt;
	}	

	if (ofGetKeyPressed(OF_KEY_UP)) {
		m_position += ofVec2f(cos(m_rotation), sin(m_rotation)) * m_speed * dt;
	}
	if (ofGetKeyPressed(OF_KEY_DOWN)) {
		m_position -= ofVec2f(cos(m_rotation), sin(m_rotation)) * m_speed * dt;
	}

	m_lastFire += dt;
	if (ofGetKeyPressed(OF_KEY_LEFT_CONTROL) && m_lastFire > m_fireDelay) {
		GameManager::instance().add(new Bullet(m_position, m_rotation));
		m_lastFire = 0;
	}
}

void Ship::draw() {
	ofPushMatrix();
	ofTranslate(m_position);
	ofRotateZ(ofRadToDeg(m_rotation) + 90);
	m_image->draw(0,0);
	ofPopMatrix();
}
