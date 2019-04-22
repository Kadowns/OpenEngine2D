#include "TintSprite.h"
#include "ofGraphics.h"

TintSprite::TintSprite(GameObject* attached, const char* imageName) : Sprite(attached, imageName) {

}

TintSprite::~TintSprite(){

}

void TintSprite::setColor(const ofColor& color) {
    m_tintColor = color;
}

void TintSprite::draw() {
    ofSetColor(m_tintColor);
	Sprite::draw();
    ofSetColor(ofColor::white);
}