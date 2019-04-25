#pragma once

#include "../core/GameObject.h"
#include "../core/Renderable.h"

struct Star {
    Star();
    ~Star();

    void isInsideWindow(const ofVec2f& windowSize, const ofVec2f& center);
	void update();

	
    ofVec2f position;
    float radius, alpha = 255, randomOffset, randomOsccilation;
};


class StarBackground : public GameObject, public Renderable {

public:

    StarBackground(size_t starCount);
    ~StarBackground();



private:

    ofVec2f m_lastCameraPosition, m_targetPosition;

    std::vector<Star> m_stars;

    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;
	
    //Inherited via Renderable
    virtual void draw() override;
	inline virtual ofVec2f position() const override;
};
