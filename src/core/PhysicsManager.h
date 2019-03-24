#pragma once

#include <vector>

class Collider;
class CircleCollider;
class Rigidbody2D;

class PhysicsManager {

public:

    static void bind(Collider* col);
    static void bind(Rigidbody2D* rb);

    static void unbind(Collider* col);
    static void unbind(Rigidbody2D* col);

    static void update(float dt);    

private:

    static std::vector<Collider*> m_colliders;
    static std::vector<Rigidbody2D*> m_rigidbodies;


};
