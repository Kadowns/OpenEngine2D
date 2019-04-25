#pragma once

#include "../core/Sprite.h"

class TintSprite : public Sprite {

public:

    TintSprite(GameObject* attached, const char* imageName);
    ~TintSprite();
	
    void setColor(const ofColor& color);

private:

    ofColor m_tintColor;

    virtual void draw() override;

};
