#include "Ship.h"

#include "../core/Timer.h"
#include "../core/Overloads.h"
#include "../core/ScenePlayer.h"
#include "../core/InputManager.h"
#include "../core/CircleCollider.h"
#include "../core/DataManager.h"
#include "../core/Rigidbody2D.h"

#include "Bullet.h"
#include "Missile.h"
#include "Asteroid.h"
#include "CameraController.h"
#include "ThrusterParticles.h"
#include "ExplosionParticle.h"
#include "TintSprite.h"




Ship::Ship(const int& playerNumber, const ofVec2f& position, TEAM team) {
    
    transform.position = position;

    m_team = team;
    m_sprite = new TintSprite(this, "ship");
    m_rb = new Rigidbody2D(&transform, 1, 2.0f, 1.5f, 0.0f);
    m_collider = new CircleCollider(this, &transform, m_rb, 65);
    m_thruster = new ThrusterParticles(transform.position, 250, transform.getRight(), 0.01f);
    ScenePlayer::instance().add(m_thruster);

    m_shootAudio = DataManager::getSound("shoot");
    m_shootAudio->setVolume(0.5f);

	m_onCollisionWithCallback = [this](GameObject* other) {
		this->onCollisionWith(other);
	};
	m_collider->onCollisionWith += &m_onCollisionWithCallback;
    
	auto number = std::to_string(playerNumber);
    m_buttonRight = "turnright" + number;
    m_buttonLeft = "turnleft" + number;
    m_buttonForward = "forward" + number;
    m_buttonBackward = "backward" + number;
    m_buttonFire = "fire" + number;
    m_buttonMissile = "special" + number;
}

Ship::~Ship() {	
	m_collider->onCollisionWith -= &m_onCollisionWithCallback;
    delete m_collider;
    delete m_sprite;
    delete m_rb;
}

void Ship::onCollisionWith(GameObject* other) {
	auto asteroid = dynamic_cast<Asteroid*>(other);
	if (asteroid != nullptr) {
        DataManager::getSound("hit")->play();
		asteroid->destroy();
		m_rb->addForce((transform.position - asteroid->transform.position).getNormalized() * 300, Rigidbody2D::IMPULSE);
		CameraController::instance().shake(1.0f, 1.5f);
        stop();
        m_wasHit = true;
        m_hp--;
        if (m_hp <= 0) {
            ScenePlayer::instance().destroy(this);
            ScenePlayer::instance().add(new ExplosionParticle(transform.position, 150, 150, 10));
        }
	}
}

ofVec2f Ship::getVelocity() const {
	return m_rb->getVelocity();
}

void Ship::setup() {
}

void Ship::update(float dt) {

    if (m_wasHit) {
        m_recoverTimer += dt;
        m_sprite->setColor(lerp(ofColor::red, ofColor::white, m_recoverTimer / m_recoveryTime));
        if (m_recoverTimer > m_recoveryTime) {
            m_wasHit = false;
            m_recoverTimer = 0;
            m_sprite->setColor(ofColor::white);
        }
        else {
            return;
        }
    }

    //Inputs-----------------------------------------------------
	if (InputManager::getButtonDown(m_buttonRight)) {        
        m_rb->addTorque(DEG_TO_RAD * 360);
	}
	if (InputManager::getButtonDown(m_buttonLeft)) {        
        m_rb->addTorque(-DEG_TO_RAD * 360);
	}	

	if (InputManager::getButtonDown(m_buttonForward)) {  
        move(transform.getRight());
    }
    else if (InputManager::getButtonReleased(m_buttonForward)) {
        stop();
    }
	if (InputManager::getButtonDown(m_buttonBackward)) {
        move(-transform.getRight());
    }
    else if (InputManager::getButtonReleased(m_buttonBackward)) {
        stop();
    }

	m_lastFire += dt;
	if (InputManager::getButtonDown(m_buttonFire) && m_lastFire > m_fireDelay) {
        shoot();
		m_lastFire = 0;
	}

    m_lastMissile += dt;
    if (InputManager::getButtonDown(m_buttonMissile) && m_lastMissile > m_missileDelay) {
        missile();
        m_lastMissile = 0;
    }
    //Inputs//----------------------------------------
}

void Ship::move(const ofVec2f& direction) {
    m_rb->addForce(direction * m_speed);
    m_thruster->transform.position = transform.position - direction * 40;
    m_thruster->setDirection(-direction);
    m_thruster->play();
}

void Ship::stop() {
    m_thruster->stop();
}

void Ship::shoot() {
    transform.position += -transform.getRight();
    m_rb->addForce(-transform.getRight() * 25, Rigidbody2D::IMPULSE);
    ScenePlayer::instance().add(new Bullet(transform.position + transform.getRight() * 80, transform.rotation, m_team));
    CameraController::instance().shake(0.5f, 1.0f);
    m_shootAudio->play();
}

void Ship::missile() {
    ScenePlayer::instance().add(new Missile(transform.position, transform.rotation, m_team));
}
