#include "ExplosionParticle.h"

ExplosionParticle::ExplosionParticle(const float& spawnRate, const ofVec2f & position, const float & duration, const uint8_t & maxParticles)
    : ParticleSystem(position, maxParticles) {
    m_spawnRate = spawnRate;
    m_duration = duration;
}

ExplosionParticle::~ExplosionParticle() {

}

void ExplosionParticle::onUpdate(float dt) {
    m_spawnTimer += dt;
    if (m_spawnTimer > m_spawnRate) {
        
        Particle::ParticleSettings settings = {};
        settings.position = ofVec2f(0);
        settings.size = ofRandom(3, 10);
        settings.lifeTime = m_duration / 10;
        float angle = ofRandom(0, 360) * DEG_TO_RAD;
        settings.velocity = ofVec2f(cos(angle), sin(angle)) * ofRandom(40, 400);

        auto particle = addParticle();
        particle->spawn(settings);

        m_spawnTimer = 0;
    }

    m_timer += dt;
    if (m_timer > m_duration) {
        GameManager::instance().destroy(this);
    }
}

void ExplosionParticle::setup() {

}
