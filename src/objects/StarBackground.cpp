#include "StarBackground.h"

#include "../core/Overloads.h"
#include "../core/Timer.h"
#include "../core/Camera.h"
#include "../core/GameRenderer.h"

StarBackground::StarBackground(size_t starCount) {
    m_stars.resize(starCount);
    m_layerOrder = 255;

    GameRenderer::add(this);
}

StarBackground::~StarBackground() {
    m_stars.clear();
    GameRenderer::remove(this);
}

void StarBackground::setup() {
    auto wh = Camera::mainCamera().halfScreenSize();
    for (size_t i = 0; i < m_stars.size(); i++) {
        m_stars[i].position = ofVec2f(ofRandom(-wh.x, wh.x), ofRandom(-wh.y, wh.y)) * 2.0f;
        m_stars[i].radius = ofRandom(0.1f, 1.5f);
    }
    m_lastCameraPosition = Camera::mainCamera().transform.position;
    transform.position = m_lastCameraPosition;
}

void StarBackground::update(float dt) {
	transform.position += (Camera::mainCamera().transform.position - m_lastCameraPosition) * 0.1f; 
	m_lastCameraPosition = Camera::mainCamera().transform.position;
	transform.scale = 1 / Camera::mainCamera().transform.scale;
    auto windowSize = Camera::mainCamera().halfScreenSize();
	for (auto& it : m_stars) {        
		it.update();
		//it.isInsideWindow(windowSize, transform.position);
	}   
}

ofVec2f StarBackground::position() const {
	return transform.position;
}

void StarBackground::draw() {
    ofPushMatrix();       
	ofTranslate(Camera::mainCamera().transform.position);
	ofScale(transform.scale, transform.scale);
	ofTranslate(-transform.position);
	ofRotateZ(RAD_TO_DEG * transform.rotation);

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
