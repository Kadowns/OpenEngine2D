#include "StarBackground.h"

#include "../core/Overloads.h"
#include "../core/Timer.h"
#include "../core/Camera.h"
#include "../core/GameRenderer.h"
#include "../core/EventManager.h"

StarBackground::StarBackground(size_t starCount) {
    m_stars.resize(starCount);
    m_layerOrder = 255;

    m_onMouseClickCallback = [this](int x, int y) {
        this->onMouseClicked(x, y);
    };
    EventManager::onMousePressed += &m_onMouseClickCallback;
    GameRenderer::add(this, false);
}

StarBackground::~StarBackground() {
    m_stars.clear();
    EventManager::onMousePressed -= &m_onMouseClickCallback;
    GameRenderer::remove(this, false);
}

void StarBackground::onMouseClicked(int x, int y) {
    m_lastClickPosition = ofVec2f(x, y) - Camera::mainCamera().halfScreenSize();
    m_targetPosition = transform.position + m_lastClickPosition;    
}

void StarBackground::setup() {
    auto wh = Camera::mainCamera().halfScreenSize();
    for (size_t i = 0; i < m_stars.size(); i++) {
        m_stars[i].position = ofVec2f(ofRandom(-wh.x, wh.x), ofRandom(-wh.y, wh.y)) * 2.0f;
        m_stars[i].radius = ofRandom(0.1f, 1.5f);
    }
    m_lastClickPosition = Camera::mainCamera().transform.position;
    transform.position = m_lastClickPosition;
}

void StarBackground::update(float dt) {
    transform.position = lerp(transform.position, m_targetPosition, 2.0f * dt);
	//m_lastClickPosition = Camera::mainCamera().transform.position;
    //transform.rotation = Camera::mainCamera().transform.rotation;
    transform.scale = 1 / Camera::mainCamera().transform.scale;
    auto windowSize = Camera::mainCamera().halfScreenSize();
	for (auto& it : m_stars) {
        //it.isInsideWindow(windowSize, transform.position);
		it.update();
	}   
}

void StarBackground::draw() {
    ofPushMatrix();       
	//essa merda não funciona

    /*ofTranslate(m_halfWindowSize);
    ofRotateZ(RAD_TO_DEG * transform.rotation);
    ofScale(transform.scale, transform.scale);
    ofTranslate(-transform.position);*/

    ofTranslate(Camera::mainCamera().transform.position);
    ofScale(transform.scale, transform.scale);	
    ofTranslate(-transform.position);

    for (auto& it : m_stars) {
		ofSetColor(255, it.alpha);
        ofDrawCircle(it.position,  it.radius);
    }
	ofSetColor(ofColor::white);
    ofPopMatrix();
}

Star::Star() {
	randomOffset = ofRandom(0, 360 * DEG_TO_RAD);
	randomOsccilation = ofRandom(0.5f, 3.0f);
}

Star::~Star() {

}

void Star::isInsideWindow(const ofVec2f& windowSize, const ofVec2f& center) {

    //auto screenPos = Camera::mainCamera().screenToWorld
    if (center.x + position.x > windowSize.x * 2) {
        position.x -= windowSize.x;
    }
    else if (center.x + position.x < -windowSize.x * 2) {
        position.x += windowSize.x;
    }

    if (center.y + position.y > windowSize.y * 2) {
        position.y -= windowSize.y;
    }
    else if (center.y + position.y < -windowSize.y * 2) {
        position.y += windowSize.y;
    }
}

void Star::update() {	
	alpha = (((sin(Timer::time() * randomOsccilation + randomOffset) ) + 1.0f) / 2.0f) * 255;
}
