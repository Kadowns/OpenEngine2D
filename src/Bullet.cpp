#include "Bullet.h"
#include "DataLoader.h"
#include "ofGraphics.h"
#include "Ship.h"

#include "GameManager.h"

Bullet::Bullet(const ofVec2f& position, const float& rotation, TEAM team) {
	m_position = position;
	m_rotation = rotation;
	m_image = DataLoader::instance().getImage("bullet");
	m_team = team;
	m_collider.first = this;
	m_collider.second = new ofRectangle(
		m_position,
		m_image->getWidth(),
		m_image->getHeight()
	);
}

Bullet::~Bullet() {
	GameManager::instance().unsubscribeFromCollision(&m_collider);
}

void Bullet::setup() {
	GameManager::instance().subscribeToCollision(&m_collider);

	auto ships = GameManager::instance().search<Ship>();

}

void Bullet::update(float dt) {
	m_position += ofVec2f(cos(m_rotation), sin(m_rotation)) * m_speed * dt;
	m_collider.second->position = m_position;
}

void Bullet::draw() {
	ofPushMatrix();
	ofTranslate(m_position);
	ofRotateZ(ofRadToDeg(m_rotation));
	m_image->draw(0, 0);
	ofPopMatrix();	
}
