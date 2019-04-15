#include "ExplosionParticle.h"

ExplosionParticle::ExplosionParticle(const ofVec2f & position, const uint8_t & maxParticles, uint8_t burstCount, float duration)
    : ParticleSystem(position, maxParticles) {
    m_burstCount = burstCount;
    m_duration = duration;
}

ExplosionParticle::~ExplosionParticle() {

}

void ExplosionParticle::onUpdate(float dt) {
    
    m_timer += dt;
    if (m_timer > m_duration) {
        GameManager::instance().destroy(this);
    }
}

void ExplosionParticle::setup() {

    Particle::ParticleSettings settings = {};
    settings.position = ofVec2f(0);
    settings.size = ofRandom(0.5, 3.5f);
    settings.lifeTime = m_duration;

    for (uint8_t i = 0; i < m_burstCount; i++) {      
        float angle = ofRandom(0, 360) * DEG_TO_RAD;
        settings.velocity = ofVec2f(cos(angle), sin(angle)) * ofRandom(40, 400);
        auto particle = addParticle();
        particle->spawn(settings);
    }
}
