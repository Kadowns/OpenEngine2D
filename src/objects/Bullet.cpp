#include "Bullet.h"

#include "ofGraphics.h"

#include <limits>

#include "../core/DataLoader.h"
#include "../core/GameManager.h"
#include "../core/Collider.h"
#include "../core/Sprite.h"
#include "Ship.h"


Bullet::Bullet(const ofVec2f& position, const float& rotation, TEAM team) {
    transform.position = position;
    transform.rotation = rotation;
    m_team = team;
    m_sprite = new Sprite(this, "bullet");	
    m_collider = new Collider(this, &transform.position, m_sprite->getWidth(), m_sprite->getHeight());

    m_onCollisionCallback = [this](GameObject* go) {
        this->onCollisionWith(go);
    };
    m_collider->onCollisionWith += &m_onCollisionCallback;
}

Bullet::~Bullet() {	
    delete m_collider;
    delete m_sprite;
}

void Bullet::setup() {	

	auto ships = GameManager::instance().search<Ship>();

    float mindist = std::numeric_limits<float>::max();
    for (auto it : ships) {
        if (it->getTeam() != m_team) {
            float dist = (transform.position - it->transform.position).length();
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
    transform.position += transform.getRight() * m_speed * dt;

    if (m_target != nullptr) {
        auto dist = (m_target->transform.position - transform.position).getNormalized();
        float targetRotation = atan2f(dist.y, dist.x);
        transform.rotation = ofLerpRadians(transform.rotation, targetRotation, 0.02f);
    }    	
}

void Bullet::draw() {
    m_sprite->draw();
}
