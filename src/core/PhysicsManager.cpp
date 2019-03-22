#include "PhysicsManager.h"
#include "Collider.h"


std::vector<Collider*> PhysicsManager::m_colliders;

void PhysicsManager::bind(Collider* col) {
    m_colliders.push_back(col);
}

void PhysicsManager::unbind(Collider* col) {
    m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), col));
}

void PhysicsManager::update() {
    //testa colisões---------------------------------
    for (size_t i = 0; i < m_colliders.size(); i++) {
        for (size_t j = 0; j < m_colliders.size(); j++) {
            if (i <= j) {
                continue;
            }

            m_colliders[i]->tryCollision(*m_colliders[j]);
        }
    }
    //-----------------------------------------------
}
