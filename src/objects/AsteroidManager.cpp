#include "AsteroidManager.h"

#include "../core/Timer.h"
#include "../core/Camera.h"

#include "Ship.h"
#include "Asteroid.h"

AsteroidManager::AsteroidManager(float spawnInterval) {
	m_timeToSpawn = spawnInterval;
	m_timeToNextSpawn = spawnInterval + Timer::time();
	
	m_onWindowResizeCallback = [this](int x, int y) {
		this->onWindowResized(x, y);
	};
	EventManager::onWindowResized += &m_onWindowResizeCallback;
}

AsteroidManager::~AsteroidManager() {
	EventManager::onWindowResized -= &m_onWindowResizeCallback;
}

void AsteroidManager::onWindowResized(int x, int y) {
	m_windowSize.set(x, y);
}


void AsteroidManager::setup() {
	m_target = ScenePlayer::instance().search<Ship>()[0];
}

void AsteroidManager::update(float dt) {
	if (Timer::time() >= m_timeToNextSpawn) {
		m_timeToNextSpawn = Timer::time() + m_timeToSpawn;
		spawnAsteroid();
	}
}


void AsteroidManager::spawnAsteroid() {
	
    auto target = m_target.lock();
    if (target) {
        ofVec2f spawnPosition;
        int rand = ofRandom(0, 3);
        switch (rand) {
        case 0:
            spawnPosition = ofVec2f(-m_windowSize.x, ofRandom(0, m_windowSize.y));
            break;
        case 1:
            spawnPosition = ofVec2f(m_windowSize.x, ofRandom(0, m_windowSize.y));
            break;
        case 2:
            spawnPosition = ofVec2f(ofRandom(0, m_windowSize.x), -m_windowSize.y);
            break;
        default:
            spawnPosition = ofVec2f(ofRandom(0, m_windowSize.x), m_windowSize.y);
            break;
        }
        spawnPosition *= 1 / Camera::mainCamera().transform.scale;
        spawnPosition.rotate(Camera::mainCamera().transform.rotation);
        spawnPosition += target->transform.position;

        ofVec2f velocity = (target->transform.position - spawnPosition).normalized() * ofRandom(100, 700);
        float angularVelocity = ofRandom(-360, 360) * DEG_TO_RAD;

        ScenePlayer::instance().add(new Asteroid(spawnPosition, velocity, angularVelocity, Asteroid::BIG));
    }
}