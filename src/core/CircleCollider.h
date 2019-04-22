#pragma once

#include "Collider.h"

class CircleCollider : public Collider {

public:

    CircleCollider(GameObject* pAttached, Transform2D* pTransform, Rigidbody2D* rb, float radius);
    virtual ~CircleCollider();
    float getRadius() const;

    static bool circleVsCircle(CircleCollider* a, CircleCollider* b);

private:

    float m_radius;
    // Inherited via Collider
    virtual void tryCollision(Collider * other) override;
    virtual ofRectangle getAABB() override;

};
