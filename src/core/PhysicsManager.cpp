#include "PhysicsManager.h"

#include "CircleCollider.h"
#include "Rigidbody2D.h"


std::vector<Collider*> PhysicsManager::m_colliders;
std::vector<Rigidbody2D*> PhysicsManager::m_rigidbodies;
QuadTree<Collider>* PhysicsManager::m_qt = new QuadTree<Collider>(ofRectangle(-5012, -5012, 10024, 10024), 1);

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

    m_qt->clear();
    for (auto& it : m_colliders) {
        m_qt->insert(QuadTree<Collider>::Point(it->transform().position, it));
    }

    //testa colisões---------------------------------
    for (size_t i = 0; i < m_colliders.size(); i++) {
        std::vector<QuadTree<Collider>::Point> found;
        m_qt->query(m_colliders[i]->getAABB(), found);

        for (size_t j = 0; j < found.size(); j++) {
            if (m_colliders[i]->transform().position == found[j].position) {
                continue;
            }
            m_colliders[i]->tryCollision(found[j].data);
        }

        /*for (size_t j = 0; j < m_colliders.size(); j++) {
            if (i <= j) {
                continue;
            }
            m_colliders[i]->tryCollision(m_colliders[j]);
        }*/
    }
    
    //-----------------------------------------------
}

QuadTree<Collider>* PhysicsManager::getQT() {
    return m_qt;
}


