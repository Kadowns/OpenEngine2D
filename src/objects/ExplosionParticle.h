#pragma once

#include "../core/ParticleSystem.h"


class ExplosionParticle : public ParticleSystem {
public:

    ExplosionParticle(const ofVec2f& position, const uint8_t& maxParticles, uint8_t burstCount, float totalDuration);
    virtual ~ExplosionParticle();

private:

    float m_duration, m_timer = 0;    
    uint8_t m_burstCount;
    // Inherited via ParticleSystem
    virtual void setup() override;
    virtual void onUpdate(float dt) override;  
};
