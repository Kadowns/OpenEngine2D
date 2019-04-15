#pragma once

#include "ofImage.h"

#include "Renderable.h"

class GameObject;

class Sprite : Renderable {
public:

    Sprite(GameObject* attached, const char* imageName);
    ~Sprite();

    virtual void draw() override;

    float getWidth();
    float getHeight();


private:

    GameObject* m_attached;
    ofImage* m_image;


	// Inherited via Renderable
	inline virtual ofVec2f position() const override;

};
