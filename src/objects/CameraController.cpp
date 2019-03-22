#include "CameraController.h"

#include "../core/Overloads.h"
#include "../core/EventManager.h"
#include "../core/InputManager.h"

CameraController::CameraController() {
    m_onMouseReleasedCallback = [this](int x, int y, int key) {
        if (InputManager::getButtonReleased("leftMouse")) {
            this->onMouseReleased(x, y);
        }
    };
    EventManager::onMouseReleased += &m_onMouseReleasedCallback;

    m_onMousePressedCallback = [this](int x, int y, int key) {
        if (InputManager::getButtonPressed("leftMouse")) {
            this->onMousePressed(x, y);
        }
    };
    EventManager::onMousePressed += &m_onMousePressedCallback;
}

CameraController::~CameraController() {
    EventManager::onMouseReleased -= &m_onMouseReleasedCallback;
    EventManager::onMousePressed -= &m_onMousePressedCallback;
}

void CameraController::onMousePressed(int x, int y) {
    m_dragDelta = x;
}

void CameraController::onMouseReleased(int x, int y) {
    m_target = Camera::mainCamera().screenToWorld(ofVec2f(x, y));
    m_dragDelta -= x;
}

void CameraController::setup() {

}

void CameraController::update(float dt) {    
    Camera::mainCamera().transform.position = lerp(Camera::mainCamera().transform.position, m_target, 0.1f);

    if (!InputManager::getButtonDown("leftMouse")) {
        Camera::mainCamera().transform.rotation = ofLerp(Camera::mainCamera().transform.rotation, ofDegToRad(m_dragDelta), 0.1f);
    }
}

void CameraController::draw() {

}
