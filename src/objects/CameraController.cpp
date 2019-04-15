#include "CameraController.h"

#include "../core/Overloads.h"
#include "../core/EventManager.h"
#include "../core/InputManager.h"

#include "Ship.h"

CameraController* CameraController::s_instance = nullptr;

CameraController::CameraController() {
    
    s_instance = this;

    m_onMousePressedCallback = [this](int x, int y) {
        if (InputManager::getButtonPressed("leftMouse")) {
            this->onMousePressed(x, y);
        }
        else if (InputManager::getButtonPressed("rightMouse")) {
            this->onRightMousePressed(x);
        }
    };
    EventManager::onMousePressed += &m_onMousePressedCallback;  

    m_onMouseDragCallback = [this](int x, int y) {
        if (InputManager::getButtonDown("rightMouse")) {
            this->onRightMouseDrag(x, y);
        }        
    };
    EventManager::onMouseDragged += &m_onMouseDragCallback;

    m_onMouseScrollCallback = [this](int x, int y, float scrollX, float scrollY) {
        this->onMouseScroll(x, y, scrollY);
    };
	EventManager::onMouseScrolled += &m_onMouseScrollCallback;
}

CameraController::~CameraController() {    
    s_instance = nullptr;
    EventManager::onMousePressed -= &m_onMousePressedCallback;
    EventManager::onMouseDragged -= &m_onMouseDragCallback;
    EventManager::onMouseScrolled -= &m_onMouseScrollCallback;
}

void CameraController::onMousePressed(int x, int y) {
    m_target = Camera::mainCamera().screenToWorld(ofVec2f(x, y));    
}

void CameraController::onRightMousePressed(int x) {    
    m_dragDelta = x;
}

void CameraController::onRightMouseDrag(int x, int y) {    
    m_targetRotation += ofDegToRad((m_dragDelta - x));
    m_dragDelta = x;
}

void CameraController::onMouseScroll(int x, int y, float scroll) {    
    m_scrollAmount += scroll * 0.1f;
    if (m_scrollAmount < 0.1f) {
        m_scrollAmount = 0.1f;
    }
    else if(m_scrollAmount > 1.75f) {
        m_scrollAmount = 1.75f;
    }
}

void CameraController::shake(float duration, float intensity) {
    m_shake.timer = 0;
    m_shake.duration = duration;
    m_shake.intensity = intensity;
    m_shake.initialIntensity = intensity;
    m_shake.shaking = true;    
}

CameraController& CameraController::instance() {
    return *s_instance;
}

void CameraController::setup() {
    m_target = Camera::mainCamera().transform.position;

	m_defaultTarget = GameManager::instance().search<Ship>()[0];
}

void CameraController::update(float dt) {

	m_target = m_defaultTarget->transform.position;
	m_targetRotation = -m_defaultTarget->transform.rotation - 90 * DEG_TO_RAD;

	Camera::mainCamera().transform.position = lerp(Camera::mainCamera().transform.position, m_target, m_smootSpeed * dt);
	Camera::mainCamera().transform.scale = ofLerp(Camera::mainCamera().transform.scale, m_scrollAmount, m_smootSpeed * dt);
	Camera::mainCamera().transform.rotation = ofLerp(Camera::mainCamera().transform.rotation, m_targetRotation, m_smootSpeed * dt);

    if (m_shake.shaking) {
        m_shake.timer += dt;
        Camera::mainCamera().transform.position += ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)) * m_shake.intensity;
        Camera::mainCamera().transform.rotation += ofRandom(-1, 1) * m_shake.intensity * DEG_TO_RAD;
        m_shake.intensity = ofLerp(m_shake.initialIntensity, 0, m_shake.timer / m_shake.duration);
        if (m_shake.timer > m_shake.duration) {
            m_shake.shaking = false;
        }
    }

}