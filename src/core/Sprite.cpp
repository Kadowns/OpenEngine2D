#include "Sprite.h"

#include "ofGraphics.h"

#include "GameRenderer.h"
#include "DataManager.h"
#include "GameObject.h"

Sprite::Sprite(GameObject* attached, const char* imageName) {
    m_attached = attached;
    m_image = DataManager::getImage(imageName);
    GameRenderer::add(this);
}

Sprite::~Sprite() {
    GameRenderer::remove(this);
}

void Sprite::draw() {
    ofPushMatrix();
    ofTranslate(m_attached->transform.position);
    ofRotateZ(ofRadToDeg(m_attached->transform.rotation));
    m_image->draw(0, 0);
    ofPopMatrix();
}

float Sprite::getWidth() {
    return m_image->getWidth();
}

float Sprite::getHeight() {
    return m_image->getHeight();
}
