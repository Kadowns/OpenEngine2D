#include "Collider.h"
#include "../core/PhysicsManager.h"

Collider::Collider(GameObject* pAttached, ofVec2f * pPosition, float w, float h) {
    p_attached = pAttached;
    p_position = pPosition;
    m_rec.set(*pPosition, w, h);
    PhysicsManager::bind(this);
}

Collider::~Collider() {
    PhysicsManager::unbind(this);
}

void Collider::tryCollision(Collider& other) {
    updatePosition();
    other.updatePosition();
    if (m_rec.intersects(other.getRectangle())) {
        onCollisionWith(other.getAttachedGameObject());
        other.onCollisionWith(p_attached);
    }
}

void Collider::updatePosition() {
    m_rec.position = *p_position;
}

GameObject* Collider::getAttachedGameObject() {
    return p_attached;
}

const ofRectangle& Collider::getRectangle() {
    return m_rec;
}
