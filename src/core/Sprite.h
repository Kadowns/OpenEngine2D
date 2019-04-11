#pragma once

#include "ofImage.h"

#include "IRenderable.h"

class GameObject;

class Sprite : IRenderable {
public:

    Sprite(GameObject* attached, const char* imageName);
    ~Sprite();

    virtual void draw() override;

    float getWidth();
    float getHeight();


private:

    GameObject* m_attached;
    ofImage* m_image;


	// Inherited via IRenderable
	inline virtual ofVec2f position() const override;

};
