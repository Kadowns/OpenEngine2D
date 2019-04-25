#pragma once

#include "../core/GameObject.h"
#include "Team.h"

class TintSprite;
class Collider;
class Rigidbody2D;
class ofSoundPlayer;
class ThrusterParticles;

class Ship : public GameObject, public Team {
private:

    TintSprite* m_sprite;
    Collider* m_collider;
    Rigidbody2D* m_rb;
    ofSoundPlayer* m_shootAudio;
    ThrusterParticles* m_thruster;

	float m_speed = 1445.0f;
	float m_fireDelay = 0.05f, m_lastFire = 0;	
    float m_missileDelay = 0.5f, m_lastMissile = 0;
    float m_recoveryTime = 1.25f, m_recoverTimer = 0;

    int m_hp = 6;

    bool m_wasHit = false;
	
    std::string m_buttonRight, m_buttonLeft, m_buttonForward, m_buttonBackward, m_buttonFire, m_buttonMissile;

	Event<GameObject*>::EventListener m_onCollisionWithCallback;

    void move(const ofVec2f& direction);
    void stop();
    void shoot();
    void missile();

public:

	Ship(const int& playerNumber, const ofVec2f& position, TEAM team);
	~Ship();


	void onCollisionWith(GameObject* other);

	ofVec2f getVelocity() const;

	// Inherited via GameObject
	virtual void setup() override;
	virtual void update(float dt) override;
};

