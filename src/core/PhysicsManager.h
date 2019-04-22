#pragma once

#include <vector>

#include "QuadTree.h"

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

    static QuadTree<Collider>* getQT();

private:

    static QuadTree<Collider>* m_qt;

    static std::vector<Collider*> m_colliders;
    static std::vector<Rigidbody2D*> m_rigidbodies;


};
