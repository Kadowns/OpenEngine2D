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
    transform.rotation = rotation + ofRandom(-15, 15) * DEG_TO_RAD;
    m_targetRotation = rotation;
    m_team = team;
    m_sprite = new Sprite(this, "bullet");
    m_rb = new Rigidbody2D(&transform, 0.01f, 0.3f, 0.9f, 0.7f);
    m_collider = new CircleCollider(this, &transform, m_rb, 50);
    

    m_onCollisionCallback = [this](GameObject* go) {
        this->onCollisionWith(go);
    };
    m_collider->onCollisionWith += &m_onCollisionCallback;
}

Bullet::~Bullet() {	
    m_collider->onCollisionWith -= &m_onCollisionCallback;
    delete m_collider;
    delete m_sprite;
    delete m_rb;
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
    m_rb->addForce(transform.getRight() * m_speed, Rigidbody2D::IMPULSE);
}

void Bullet::update(float dt) {    
    transform.rotation = ofLerpRadians(transform.rotation, m_targetRotation, 0.1f);   
}
