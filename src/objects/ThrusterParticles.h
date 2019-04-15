#pragma once

#include "../core/ParticleSystem.h"

class Ship;

class ThrusterParticles : public ParticleSystem {


public:
    ThrusterParticles(const ofVec2f& position, const uint8_t& maxParticles, const ofVec2f& direction, const float& spawnRate);
    void setDirection(const ofVec2f& direction);

private:    

    float m_spawnRate, m_spawnTimer = 0;
    ofVec2f m_direction;
    // Inherited via ParticleSystem
    virtual void setup() override;
    virtual void onUpdate(float dt) override;
};
