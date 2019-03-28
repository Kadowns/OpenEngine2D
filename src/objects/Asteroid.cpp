#include "Asteroid.h"

#include "../core/GameManager.h"
#include "../core/Rigidbody2D.h"
#include "../core/CircleCollider.h"
#include "../core/Sprite.h"

#include "Ship.h"


Asteroid::Asteroid(const ofVec2f & position, const ofVec2f & initialVelocity, float initialAngularVelocity, ASTEROID_TYPE type) {

    m_type = type;
    switch (m_type) {
    case BIG:
        transform.scale = 4.0f;
        break;
    case SMALL:
        transform.scale = 1.5f;
        break;
    }
    transform.position = position;


    m_sprite = new Sprite(this, "asteroid");
    m_rb = new Rigidbody2D(&transform, 5.0f, 0, 0, 0.5f);
    m_rb->addForce(initialVelocity, Rigidbody2D::IMPULSE);
    m_rb->addTorque(initialAngularVelocity, Rigidbody2D::IMPULSE);
    m_collider = new CircleCollider(this, &transform, m_rb, 1 * transform.scale);
    m_onCollisionWithCallback = [this](GameObject* other) {
        this->onCollisionWith(other);
    };
    m_collider->onCollisionWith += &m_onCollisionWithCallback;
    
}

Asteroid::~Asteroid() {
    m_collider->onCollisionWith -= &m_onCollisionWithCallback;
    delete m_sprite;
    delete m_rb;
    delete m_collider;
}

void Asteroid::onCollisionWith(GameObject* other) {
    auto ship = dynamic_cast<Ship*>(other);
    if (ship != nullptr) {
        GameManager::instance().destroy(ship);
        destroy();
    }    
}

void Asteroid::destroy() {
    if (m_type == BIG) {
        size_t asteroidsToSpawn = 3;
        for (size_t i = 0; i < asteroidsToSpawn; i++) {
			float percent = (float)i / asteroidsToSpawn;
            ofVec2f direction = ofVec2f(cos(percent * 360 * DEG_TO_RAD), sin(percent * 360 * DEG_TO_RAD));
            GameManager::instance().add(new Asteroid(transform.position + direction * 20, direction * ofRandom(80, 160), ofRandom(-180, 180), SMALL));
        }
    }
    GameManager::instance().destroy(this);
}

void Asteroid::setup() {   

}

void Asteroid::update(float dt) {

}
