#include "CircleCollider.h"
#include "Transform2D.h"
#include "Rigidbody2D.h"
#include "PhysicsManager.h"

CircleCollider::CircleCollider(GameObject* pAttached, Transform2D* pTransform, Rigidbody2D* rb, float radius) : Collider(pAttached, pTransform, rb) {
    m_radius = radius;
}

CircleCollider::~CircleCollider() {

}

float CircleCollider::getRadius() const {
    return m_radius;
}

void CircleCollider::tryCollision(Collider* other) {
    auto circle = dynamic_cast<CircleCollider*>(other);
    if (circle != nullptr) {

        
        if (CircleCollider::circleVsCircle(this, circle)) {

            if (p_rb != nullptr && circle->p_rb != nullptr) {

                float r = m_radius + circle->m_radius;
                float penetration = r - p_transform->position.distance(circle->p_transform->position);

                ofVec2f normal = (p_transform->position - circle->p_transform->position).normalize();

                ofVec2f relativeVelocity = p_rb->getVelocity() - circle->p_rb->getVelocity();

                float velocityAlongNormal = relativeVelocity.dot(normal);

                if (velocityAlongNormal > 0) {
                    return;
                }
                float e = std::min(p_rb->getRestitution(), circle->p_rb->getRestitution());


                float inverseMassA = 1 / p_rb->getMass();
                float inverseMassB = 1 / circle->p_rb->getMass();

                float massSum = inverseMassA + inverseMassB;

                float j = (-(1 + e) * velocityAlongNormal) / massSum;                

                ofVec2f impulse = j * normal;

                float ratio = inverseMassA / massSum;
                p_rb->addForce(impulse * ratio, Rigidbody2D::IMPULSE);

                ratio = inverseMassB / massSum;
                circle->p_rb->addForce(-impulse * ratio, Rigidbody2D::IMPULSE);

            }
            onCollisionWith(circle->getGameObject());
            circle->onCollisionWith(p_gameObject);
        }
    }
}

bool CircleCollider::circleVsCircle(CircleCollider* a, CircleCollider* b) {
    float r = a->m_radius + b->m_radius;
    r *= r;
    return r > a->p_transform->position.squareDistance(b->p_transform->position);
}