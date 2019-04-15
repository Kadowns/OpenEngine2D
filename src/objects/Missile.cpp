#include "Missile.h"

#include <limits>

#include "ofGraphics.h"
#include "../core/DataManager.h"
#include "../core/GameManager.h"
#include "../core/CircleCollider.h"
#include "../core/Sprite.h"

#include "Ship.h"
#include "Asteroid.h"


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

void Missile::onCollisionWith(GameObject* other) {
    auto ship = dynamic_cast<Ship*>(other);
    if (ship != nullptr) {
        if (ship->getTeam() != m_team) {
            GameManager::instance().destroy(ship);
            GameManager::instance().destroy(this);
        }        
        return;
    }

    auto asteroid = dynamic_cast<Asteroid*>(other);
    if (asteroid != nullptr) {
        asteroid->destroy();
        GameManager::instance().destroy(this);
    }
}

void Missile::setup() {

	searchTargets();
}

void Missile::update(float dt) {    
    transform.position += transform.getRight() * m_speed * dt;
    if (m_target != nullptr) {
        auto distance = m_target->transform.position - transform.position;
        auto targetRotation = atan2f(distance.y, distance.x);
        transform.rotation = ofLerpRadians(transform.rotation, targetRotation, 2.5f * dt);
	}
	else {
		searchTargets();
	}
}

void Missile::searchTargets() {
	auto asteroids = GameManager::instance().search<Asteroid>();

	float mindist = std::numeric_limits<float>::max();
	for (auto it : asteroids) {

		float dist = (transform.position - it->transform.position).length();
		if (dist < mindist) {
			m_target = it;
			mindist = dist;
		}
	}
}
