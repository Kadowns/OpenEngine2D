#include "Bullet.h"

#include <limits>

#include "ofGraphics.h"

#include "../core/GameManager.h"
#include "../core/DataManager.h"
#include "../core/CircleCollider.h"
#include "../core/Rigidbody2D.h"
#include "../core/Sprite.h"

#include "Ship.h"


Bullet::Bullet(const ofVec2f& position, const float& rotation, TEAM team) {
    transform.position = position;
    transform.rotation = rotation + ofRandom(-25, 25) * DEG_TO_RAD;
    m_targetRotation = rotation + ofRandom(-5, 5) * DEG_TO_RAD;
    m_team = team;
    m_sprite = new Sprite(this, "bullet");

    m_collider = new CircleCollider(this, &transform, nullptr, 50);
    

    m_onCollisionCallback = [this](GameObject* go) {
        this->onCollisionWith(go);
    };
    m_collider->onCollisionWith += &m_onCollisionCallback;
}

Bullet::~Bullet() {	
    m_collider->onCollisionWith -= &m_onCollisionCallback;
    delete m_collider;
    delete m_sprite;
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

void Bullet::setup() {
    
}

void Bullet::update(float dt) {    
    
    transform.position += transform.getRight() * (m_speed + m_speed * ((m_lifetime - m_timealive) / m_lifetime)) * dt;
    transform.rotation = ofLerpRadians(transform.rotation, m_targetRotation, 0.1f);   


    m_timealive += dt;
    if (m_timealive > m_lifetime) {
        GameManager::instance().destroy(this);
    }
}
