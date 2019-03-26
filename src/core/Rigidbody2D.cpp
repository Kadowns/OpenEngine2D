#include "Rigidbody2D.h"
#include "PhysicsManager.h"

Rigidbody2D::Rigidbody2D(Transform2D* pTransform, float mass, float drag, float angularDrag, float restitution) {
    p_transform = pTransform;
    m_mass = mass;
    m_drag = drag;
    m_angularDrag = angularDrag;
    m_restitution = restitution;
    PhysicsManager::bind(this);
}

Rigidbody2D::~Rigidbody2D() {
    PhysicsManager::unbind(this);
}

void Rigidbody2D::addForce(const ofVec2f& force, FORCE_MODE mode) {
    switch (mode) {
    case ACCELERATION:
        m_acceleration += force / m_mass;
        break;
    case IMPULSE:
        m_velocity += force / m_mass;
        break;
    }    
}

void Rigidbody2D::addTorque(const float& torque) {
    m_angularAcceleration = torque / m_mass;
}

void Rigidbody2D::update(float dt) {
    //velocity
    m_velocity += m_acceleration * dt;
    m_velocity = m_velocity * (1 - dt * m_drag);
    p_transform->position += m_velocity * dt;
    m_acceleration.set(0, 0);
    //------------------------------


    //angular velocity
    m_angularVelocity += m_angularAcceleration * dt;
    m_angularVelocity = m_angularVelocity * (1 - dt * m_angularDrag);
    p_transform->rotation += m_angularVelocity * dt;
    m_angularAcceleration = 0;
    //------------------------------
}

ofVec2f Rigidbody2D::getVelocity() const {
    return m_velocity;
}

float Rigidbody2D::getMass() const {
    return m_mass;
}

float Rigidbody2D::getAngularVelocity() const {
    return m_angularVelocity;
}

float Rigidbody2D::getDrag() const {
    return m_drag;
}

float Rigidbody2D::getAngularDrag() const {
    return m_angularDrag;
}

float Rigidbody2D::getRestitution() const {
    return m_restitution;
}
