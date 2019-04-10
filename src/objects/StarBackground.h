#pragma once

#include "../core/Event.h"
#include "../core/GameObject.h"
#include "../core/IRenderable.h"

struct Star {
    Star();
    ~Star();

    void isInsideWindow(const ofVec2f& windowSize, const ofVec2f& center);
	void update();

	
    ofVec2f position;
    float radius, alpha = 255, randomOffset, randomOsccilation;
};


class StarBackground : public GameObject, public IRenderable {

public:

    StarBackground(size_t starCount);
    ~StarBackground();

    void onMouseClicked(int x, int y);


private:

    ofVec2f m_lastClickPosition, m_targetPosition;

    std::vector<Star> m_stars;

    Event<int, int>::EventListener m_onMouseClickCallback;

    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;

    //Inherited via IRenderable
    virtual void draw() override;

};
