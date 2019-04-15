#pragma once

#include "../core/GameObject.h"
#include "../core/Camera.h"
#include "../core/Event.h"

class Ship;

class CameraController : public GameObject {
public:

    CameraController();
    ~CameraController();

    void onMousePressed(int x, int y);
    void onRightMousePressed(int x);
    void onRightMouseDrag(int x, int y);
    void onMouseScroll(int x, int y, float scroll);

    void shake(float duration, float intensity);

    static CameraController& instance();

private:

    static CameraController* s_instance;
    
    Event<int, int>::EventListener m_onMousePressedCallback;    
    Event<int, int>::EventListener m_onMouseDragCallback;
    Event<int, int, float, float>::EventListener m_onMouseScrollCallback;


	Ship* m_defaultTarget;
    ofVec2f m_target;
    float m_dragDelta = 0, m_targetRotation = 0, m_scrollAmount = 1, m_smootSpeed = 2.0f;

    struct {
        float intensity = 0, duration = 0, timer = 0, initialIntensity = 0;
        bool shaking = false;
    } m_shake;
   

    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;

};