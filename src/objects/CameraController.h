#pragma once

#include "../core/GameObject.h"
#include "../core/Camera.h"

#include "../Event.h"

class CameraController : public GameObject {
public:

    CameraController();
    ~CameraController();

    void onMousePressed(int x, int y);
    void onMouseReleased(int x, int y);

private:
    
    Event<int, int, int>::EventListener m_onMousePressedCallback;
    Event<int, int, int>::EventListener m_onMouseReleasedCallback;

    ofVec2f m_target;
    float m_dragDelta = 0;
   

    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;
    virtual void draw() override;

};