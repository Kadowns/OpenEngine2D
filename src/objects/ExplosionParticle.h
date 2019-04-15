#pragma once

#include "../core/ParticleSystem.h"


class ExplosionParticle : public ParticleSystem {
public:

    ExplosionParticle(const float& spawnRate, const ofVec2f& position, const float& duration, const uint8_t& maxParticles);
    virtual ~ExplosionParticle();

private:

    float m_spawnRate, m_spawnTimer = 0, m_duration, m_timer = 0;    

    // Inherited via ParticleSystem
    virtual void setup() override;
    virtual void onUpdate(float dt) override;  
};
