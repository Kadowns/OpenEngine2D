#include "PhysicsManager.h"

#include "CircleCollider.h"
#include "Rigidbody2D.h"


std::vector<Collider*> PhysicsManager::m_colliders;
std::vector<Rigidbody2D*> PhysicsManager::m_rigidbodies;

void PhysicsManager::bind(Collider* col) {
    m_colliders.push_back(col);
}

void PhysicsManager::bind(Rigidbody2D* rb) {
    m_rigidbodies.push_back(rb);
}

void PhysicsManager::unbind(Collider* col) {
    m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), col));
}

void PhysicsManager::unbind(Rigidbody2D* rb) {
    m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), rb));
}

void PhysicsManager::update(float dt) {

    //atualiza os rb-------------------
    for (auto& it : m_rigidbodies) {
        it->update(dt);
    }

    //testa colisões---------------------------------
    for (size_t i = 0; i < m_colliders.size(); i++) {
        for (size_t j = 0; j < m_colliders.size(); j++) {
            if (i <= j) {
                continue;
            }

            m_colliders[i]->tryCollision(m_colliders[j]);
        }
    }
    //-----------------------------------------------
}


