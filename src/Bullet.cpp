#include "Bullet.h"
#include "DataLoader.h"
#include "ofGraphics.h"
#include "Ship.h"

#include <limits>

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

    float mindist = std::numeric_limits<float>::max();
    for (auto it : ships) {
        if (it->getTeam() != m_team) {
            float dist = (m_position - it->getPosition()).length();
            if (dist < mindist) {
                m_target = it;
                mindist = dist;
            }
        }
    }
}

void Bullet::onCollisionWith(GameObject* other) {
    auto ship = dynamic_cast<Ship*>(other);
    if (ship == nullptr)
        return;

    if (ship->getTeam() == m_team)
        return;

    GameManager::instance().destroy(ship);
    GameManager::instance().destroy(this);
}

void Bullet::update(float dt) {
	m_position += ofVec2f(cos(m_rotation), sin(m_rotation)) * m_speed * dt;

    if (m_target != nullptr) {
        auto dist = (m_target->getPosition() - m_position).normalized();
        float targetRotation = atan2f(dist.y, dist.x);
        m_rotation = ofLerpRadians(m_rotation, targetRotation, 0.1f);        
    }    
	m_collider.second->position = m_position;
}

void Bullet::draw() {
	ofPushMatrix();
	ofTranslate(m_position);
	ofRotateZ(ofRadToDeg(m_rotation));
	m_image->draw(0, 0);
	ofPopMatrix();	
}
