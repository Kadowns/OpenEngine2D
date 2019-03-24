#include "Missile.h"

#include <limits>

#include "ofGraphics.h"
#include "../core/DataManager.h"
#include "../core/GameManager.h"
#include "../core/CircleCollider.h"
#include "../core/Sprite.h"

#include "Ship.h"


Missile::Missile(const ofVec2f & position, const float & rotation, TEAM team) {
    transform.position = position;
    transform.rotation = rotation;
    m_team = team;
    m_sprite = new Sprite(this, "missile");
    m_collider = new CircleCollider(this, &transform, nullptr, 50);


    m_onCollisionCallback = [this](GameObject* go) {
        this->onCollisionWith(go);
    };
    m_collider->onCollisionWith += &m_onCollisionCallback;
}

Missile::~Missile() {
    delete m_sprite;
    delete m_collider;
}

void Missile::onCollisionWith(GameObject * go) {
    auto ship = dynamic_cast<Ship*>(go);
    if (ship == nullptr)
        return;

    if (ship->getTeam() == m_team)
        return;

    GameManager::instance().destroy(ship);
    GameManager::instance().destroy(this);
}

void Missile::setup() {

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

void Missile::update(float dt) {    
    transform.position += transform.getRight() * m_speed * dt;
    if (m_target != nullptr) {
        auto targetRotation = transform.getRight().angleRad((m_target->transform.position - transform.position));
        transform.rotation = ofLerpRadians(transform.rotation, targetRotation, 0.1f);
    }
}
