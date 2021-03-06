#include "Camera.h"

#include "ofGraphics.h"

#include "EventManager.h"

Camera* Camera::s_instance = nullptr;

Camera& Camera::mainCamera() {
    return *s_instance;
}

Camera::Camera(ofVec2f position, float rotation, float scale, float windowW, float windowH) {
    transform.position = position;
    transform.rotation = rotation;
    transform.scale = scale;
    windowResized(windowW, windowH);
    m_onWindowResizedCallback = [this](int w, int h) {
        this->windowResized(w, h);
    };
    EventManager::onWindowResized += &m_onWindowResizedCallback;

    s_instance = this;
}

Camera::~Camera() {
    EventManager::onWindowResized -= &m_onWindowResizedCallback;
}

void Camera::bind() {
    ofPushMatrix();    
	ofTranslate(m_halfWindowSize);	
	ofRotateZ(RAD_TO_DEG * transform.rotation);	
	ofScale(transform.scale, transform.scale);	
	ofTranslate(-transform.position);
}

void Camera::unbind() {
    ofPopMatrix();
}

void Camera::windowResized(int w, int h) {
    m_halfWindowSize.set(w / 2, h / 2);
}

ofVec2f Camera::screenToWorld(const ofVec2f& point) {
	auto vec = (point - m_halfWindowSize).getRotatedRad(-transform.rotation) / transform.scale;	
    return vec + transform.position;
}

ofVec2f Camera::worldToScreen(const ofVec2f& point) {
    return (point + m_halfWindowSize).getRotatedRad(transform.rotation) * transform.scale - transform.position;
}

ofVec2f Camera::halfScreenSize() {
    return m_halfWindowSize;
}

