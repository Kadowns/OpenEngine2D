#include "ExplosionParticle.h"
#include "../core/DataManager.h"


ExplosionParticle::ExplosionParticle(const ofVec2f & position, const uint8_t & maxParticles, uint8_t burstCount, float duration)
    : ParticleSystem(position, maxParticles) {
    m_burstCount = burstCount;
    m_duration = duration;

    m_audio = DataManager::getSound("explosion");

}

ExplosionParticle::~ExplosionParticle() {

}

void ExplosionParticle::onUpdate(float dt) {
    
    m_timer += dt;
    if (m_timer > m_duration) {
        ScenePlayer::instance().destroy(this);
    }
}

void ExplosionParticle::setup() {

    Particle::ParticleSettings settings = {};
    settings.position = ofVec2f(0);
    settings.lifeTime = m_duration;

    for (uint8_t i = 0; i < m_burstCount; i++) {      
        settings.size = ofRandom(0.5, 3.5f);
        float angle = ofRandom(0, 360) * DEG_TO_RAD;
        settings.velocity = ofVec2f(cos(angle), sin(angle)) * ofRandom(40, 400);
        auto particle = addParticle();
        particle->spawn(settings);
    }
    m_audio->play();
}
