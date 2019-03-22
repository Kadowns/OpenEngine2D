#pragma once

#include <vector>

class Collider;

class PhysicsManager {

public:

    static void bind(Collider* col);

    static void unbind(Collider* col);

    static void update();

private:

    static std::vector<Collider*> m_colliders;


};
