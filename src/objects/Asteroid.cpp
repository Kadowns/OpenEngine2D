#include "Asteroid.h"

#include "../core/GameManager.h"
#include "../core/Rigidbody2D.h"
#include "../core/CircleCollider.h"
#include "../core/Sprite.h"

#include "Ship.h"


Asteroid::Asteroid(const ofVec2f& position, const ofVec2f& initialVelocity, float initialAngularVelocity, ASTEROID_TYPE type) {

    m_type = type;
    switch (m_type) {
    case BIG:
        transform.scale = 4.0f;
        m_hitPoints = 10;
        break;
    case SMALL:
        m_hitPoints = 4;
        transform.scale = 1.5f;
        break;
    }
    transform.position = position;


    m_sprite = new Sprite(this, "asteroid");
    m_rb = new Rigidbody2D(&transform, 10.0f, 0, 0, 0.4f);
    m_rb->addForce(initialVelocity, Rigidbody2D::VELOCITY_CHANGE);
    m_rb->addTorque(initialAngularVelocity, Rigidbody2D::VELOCITY_CHANGE);
    m_collider = new CircleCollider(this, &transform, m_rb, 15 * transform.scale);
    
}

Asteroid::~Asteroid() {
    delete m_sprite;
    delete m_rb;
    delete m_collider;
}

void Asteroid::applyDamage(ofVec2f direction) {
    m_hitPoints--;
    if (m_hitPoints <= 0) {
        destroy();
        return;
    }

    m_rb->addForce(direction * 20, Rigidbody2D::IMPULSE);
}

void Asteroid::destroy() {
    if (m_type == BIG) {
        size_t asteroidsToSpawn = 3;
        for (size_t i = 0; i < asteroidsToSpawn; i++) {
			float percent = (float)i / asteroidsToSpawn;
            ofVec2f direction = ofVec2f(cos(percent * 360 * DEG_TO_RAD), sin(percent * 360 * DEG_TO_RAD));
            GameManager::instance().add(new Asteroid(transform.position + direction * 20, direction * ofRandom(180, 360), ofRandom(-45, 45), SMALL));
        }
    }
    GameManager::instance().destroy(this);
}

void Asteroid::setup() {   

}

void Asteroid::update(float dt) {

}
