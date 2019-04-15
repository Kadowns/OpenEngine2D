#pragma once
#include "Transform2D.h"

class Rigidbody2D {

public:

    enum FORCE_MODE {
        ACCELERATION,
        IMPULSE,
        FORCE,
        VELOCITY_CHANGE
    };

    Rigidbody2D(Transform2D* pTransform, float mass, float drag = 0, float angularDrag = 0, float restitution = 0);
    ~Rigidbody2D();

    void addForce(const ofVec2f& force, FORCE_MODE mode = ACCELERATION);
    void addTorque(const float& torque, FORCE_MODE mode = ACCELERATION);
    void update(float dt);

    ofVec2f getVelocity() const;
    float getMass() const;    
    float getAngularVelocity() const;
    float getDrag() const;
    float getAngularDrag() const;
    float getRestitution() const;

private:

    Transform2D* p_transform;
    float m_mass, m_drag, m_angularDrag, m_restitution;

    ofVec2f m_velocity, m_acceleration;
    float m_angularVelocity = 0, m_angularAcceleration = 0;

};