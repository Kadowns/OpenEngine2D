#include "ParticleSystem.h"

#include "GameRenderer.h"

ParticleSystem::ParticleSystem(const ofVec2f & position, const uint8_t & maxParticles, bool startOnAwake, SIMULATION_SPACE space) {
    
    for (auto i = 0; i < maxParticles; i++) {
        m_particlesPool.emplace(new Particle());
    }
    m_space = space;
    m_maxParticles = maxParticles;
    transform.position = position;
    if (startOnAwake) {
        play();
    }
    GameRenderer::add(this);
}

ParticleSystem::~ParticleSystem() {
    while (!m_particlesPool.empty()) {
        auto particle = m_particlesPool.front();
        m_particlesPool.pop();
        delete particle;
    }
    GameRenderer::remove(this);
}

void ParticleSystem::play() {
    m_isPlaying = true;
}

void ParticleSystem::stop() {
    m_isPlaying = false;
}

Particle* ParticleSystem::addParticle() {

    if (m_particlesPool.empty()) {
        return nullptr;
    }

    auto particle = m_particlesPool.front();

    auto exists = std::find(m_activeParticles.begin(), m_activeParticles.end(), particle);
    if (exists == m_activeParticles.end()) {
        m_activeParticles.emplace_back(particle);
    }
    m_particlesPool.pop();
    m_particlesPool.emplace(particle);
    return particle;

}

void ParticleSystem::removeParticle(Particle* particle) {
    m_activeParticles.remove(particle);    
}

ofVec2f ParticleSystem::position() const {
    return transform.position;
}

void ParticleSystem::draw() {
    ofPushMatrix();

    if (m_space == LOCAL) {
        ofTranslate(transform.position);
    } 
    ofRotate(transform.rotation);
    ofScale(transform.scale, transform.scale);
    for (auto it : m_activeParticles) {
        ofDrawCircle(it->settings.position, it->settings.size);
    }
    ofPopMatrix();
}


void ParticleSystem::update(float dt) {
    
    while (!m_deactivatedParticles.empty()) {
        removeParticle(m_deactivatedParticles.back());
        m_deactivatedParticles.pop_back();
    }
    
    if (m_isPlaying) {
        onUpdate(dt);
    }
    
    for (auto& it : m_activeParticles) {
        if (!it->update(dt)) {
            m_deactivatedParticles.emplace_back(it);
        }
    }   
}


//particle---------------------------------------------------------
void Particle::spawn(const ParticleSettings& settings) {
    this->settings = settings;
}

Particle::Particle() {

}

Particle::~Particle() {

}

bool Particle::update(float dt) {
    settings.position += settings.velocity * dt;
    settings.timeAlive += dt;
    if (settings.timeAlive > settings.lifeTime) {
        return false;
    }
    return true;
}
