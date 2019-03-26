#include "Ship.h"

#include "../core/GameManager.h"
#include "../core/InputManager.h"
#include "../core/Sprite.h"
#include "../core/CircleCollider.h"
#include "../core/Rigidbody2D.h"

#include "Bullet.h"
#include "Missile.h"


Ship::Ship(const int& playerNumber, const ofVec2f& position, TEAM team) {
    m_sprite = new Sprite(this, "ship");	
    m_rb = new Rigidbody2D(&transform, 1, 0.1f, 0.1f, 0.0f);
    m_collider = new CircleCollider(this, &transform, m_rb, 65);
    m_team = team;
	transform.position = position;
	auto number = std::to_string(playerNumber);
    m_buttonRight = "turnright" + number;
    m_buttonLeft = "turnleft" + number;
    m_buttonForward = "forward" + number;
    m_buttonBackward = "backward" + number;
    m_buttonFire = "fire" + number;
    m_buttonMissile = "special" + number;
}

Ship::~Ship() {	
    delete m_collider;
    delete m_sprite;
    delete m_rb;
}

void Ship::setup() {	
}

void Ship::update(float dt) {

	if (InputManager::getButtonDown(m_buttonRight)) {        
        m_rb->addTorque(DEG_TO_RAD * 360);
	}
	if (InputManager::getButtonDown(m_buttonLeft)) {        
        m_rb->addTorque(-DEG_TO_RAD * 360);
	}	

	if (InputManager::getButtonDown(m_buttonForward)) {        
        m_rb->addForce(transform.getRight() * m_speed);
	}
	if (InputManager::getButtonDown(m_buttonBackward)) {        
        m_rb->addForce(-transform.getRight() * m_speed);
	}

	m_lastFire += dt;
	if (InputManager::getButtonDown(m_buttonFire) && m_lastFire > m_fireDelay) {
		GameManager::instance().add(new Bullet(transform.position, transform.rotation, m_team));
		m_lastFire = 0;
	}

    m_lastMissile += dt;
    if (InputManager::getButtonDown(m_buttonMissile) && m_lastMissile > m_missileDelay) {
        GameManager::instance().add(new Missile(transform.position, transform.rotation, m_team));
        m_lastMissile = 0;
    }
}