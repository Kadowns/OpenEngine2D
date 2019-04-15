#pragma once

#include "GameObject.h"
#include "Renderable.h"

struct Particle {

    struct ParticleSettings {
        ofVec2f velocity;
        ofVec2f position;
        float lifeTime, timeAlive = 0, size;
    };

    ParticleSettings settings;
   
    void spawn(const ParticleSettings& position);
    Particle();
    ~Particle();

    bool update(float dt);
};


class ParticleSystem : public GameObject, public Renderable {

public:

    ParticleSystem(const ofVec2f& position, const uint8_t& maxParticles);
    virtual ~ParticleSystem();

    void play();
    void stop();

protected:   

    std::list<Particle*> m_activeParticles, m_deactivatedParticles;
    bool m_isPlaying = false;

    Particle* addParticle();
    void removeParticle(Particle* particle);

    virtual void onUpdate(float dt) = 0;

private:

    uint8_t m_maxParticles;
    std::queue<Particle*> m_particlesPool;

    virtual ofVec2f position() const override;
    virtual void draw() override;

    // Inherited via GameObject
    virtual void update(float dt) override;

};