#pragma once
#include "../core/GameObject.h"
#include "../core/IRenderable.h"

struct Star {
    Star();
    Star(const ofVec2f& position, float radius);
    ~Star();

    void isInsideWindow(const ofVec2f& windowSize);

    ofVec2f position;
    float radius;

};


class StarBackground : public GameObject, public IRenderable {

public:

    StarBackground(size_t starCount);
    ~StarBackground();


private:

    ofVec2f m_lastCameraPosition;

    std::vector<Star> m_stars;

    // Inherited via GameObject
    virtual void setup() override;
    virtual void update(float dt) override;

    //Inherited via IRenderable
    virtual void draw() override;

};
