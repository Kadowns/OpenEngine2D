#include "ThrusterParticles.h"

void ThrusterParticles::setDirection(const ofVec2f& direction) {
    m_direction = direction;
}

void ThrusterParticles::setup() {

}

void ThrusterParticles::onUpdate(float dt) {
    m_spawnTimer += dt;
    if (m_spawnTimer > m_spawnRate) {
        Particle::ParticleSettings settings = {};
        settings.position = ofVec2f(0);
        settings.size = ofRandom(1, 5);
        settings.lifeTime = 0.75f;        
        settings.velocity = m_direction * ofRandom(140, 300);

        auto particle = addParticle();
        particle->spawn(settings);

        m_spawnTimer = 0;
    }
}

ThrusterParticles::ThrusterParticles(const ofVec2f & position, const uint8_t & maxParticles, const ofVec2f& direction, const float& spawnRate)
    : ParticleSystem(position, maxParticles) {
    m_direction = direction;
    m_spawnRate = spawnRate;
}
