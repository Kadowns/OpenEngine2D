#include "Ship.h"

#include "../core/GameManager.h"
#include "../core/InputManager.h"
#include "../core/Sprite.h"
#include "../core/Collider.h"

#include "Bullet.h"


Ship::Ship(const int& playerNumber, const ofVec2f& position, TEAM team) {
    m_sprite = new Sprite(this, "ship");	
    m_collider = new Collider(this, &transform.position, m_sprite->getWidth(), m_sprite->getHeight());
    m_team = team;
	transform.position = position;
	auto number = std::to_string(playerNumber);
    m_buttonRight = "turnright" + number;
    m_buttonLeft = "turnleft" + number;
    m_buttonForward = "forward" + number;
    m_buttonBackward = "backward" + number;
    m_buttonFire = "fire" + number;
}

Ship::~Ship() {	
    delete m_collider;
    delete m_sprite;
}

void Ship::setup() {	
}

void Ship::update(float dt) {

	if (InputManager::getButtonDown(m_buttonRight)) {
        transform.rotation += ofDegToRad(360) * dt;
	}
	if (InputManager::getButtonDown(m_buttonLeft)) {
        transform.rotation -= ofDegToRad(360) * dt;
	}	

	if (InputManager::getButtonDown(m_buttonForward)) {
        transform.position += transform.getRight() * m_speed * dt;
	}
	if (InputManager::getButtonDown(m_buttonBackward)) {
        transform.position -= transform.getRight() * m_speed * dt;
	}

	m_lastFire += dt;
	if (InputManager::getButtonDown(m_buttonFire) && m_lastFire > m_fireDelay) {
		GameManager::instance().add(new Bullet(transform.position, transform.rotation, m_team));
		m_lastFire = 0;
	}
}

void Ship::draw() {
    m_sprite->draw();
}
