#include "Collider.h"
#include "PhysicsManager.h"

Collider::Collider(GameObject* pAttached, Transform2D* pTransform, Rigidbody2D* rb) {
    p_gameObject = pAttached;
    p_transform = pTransform;
    p_rb = rb;
    PhysicsManager::bind(this);
}

Collider::~Collider() {
    PhysicsManager::unbind(this);
}

GameObject* Collider::getGameObject() {
    return p_gameObject;
}

