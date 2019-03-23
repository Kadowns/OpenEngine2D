#pragma once

#include "../core/GameObject.h"
#include "../core/Camera.h"

#include "../Event.h"

class CameraController : public GameObject {
public:

    CameraController();
    ~CameraController();

    void onMousePressed(int x, int y);
    void onRightMousePressed(int x);
    void onRightMouseDrag(int x, int y);
    void onMouseScroll(int x, int y, float scroll);

private:
    
    Event<int, int>::EventListener m_onMousePressedCallback;    
    Event<int, int>::EventListener m_onMouseDragCallback;
    Event<int, int, float, float>::EventListener m_onMouseScrollCallback;

    ofVec2f m_target;
    float m_dragDelta = 0, m_targetRotation = 0, m_scrollAmount = 1;
   

    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;
    virtual void draw() override;

};