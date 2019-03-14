#include "Bullet.h"
#include "DataLoader.h"
#include "ofGraphics.h"

Bullet::Bullet(const ofVec2f& position, const float& rotation) {
	m_position = position;
	m_rotation = rotation;
	m_image = DataLoader::instance().getImage("bullet");
}

Bullet::~Bullet() {
}

void Bullet::setup() {
}

void Bullet::update(float dt) {
	m_position += ofVec2f(cos(m_rotation), sin(m_rotation)) * m_speed * dt;
}

void Bullet::draw() {
	ofPushMatrix();
	ofTranslate(m_position);
	ofRotateZ(ofRadToDeg(m_rotation));
	m_image->draw(0, 0);
	ofPopMatrix();
	
}
