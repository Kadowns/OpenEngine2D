#include "QuadTreeController.h"

#include "../core/GameRenderer.h"
#include "../core/PhysicsManager.h"
#include "../core/Camera.h"

QuadTreeController::QuadTreeController() {
    GameRenderer::add(this);
}

QuadTreeController::~QuadTreeController() {

    GameRenderer::remove(this);
}


void QuadTreeController::drawQuadTree(QuadTree<Collider>* qt) {
    ofDrawRectangle(qt->getBoundary());
    if (qt->isSubdivided()) {
        auto qts = qt->getSubdividions();
        for (auto& it : qts) {
            drawQuadTree(it);
        }
    }
}

ofVec2f QuadTreeController::position() const {
    return transform.position;
}

void QuadTreeController::draw() {
    ofPushMatrix();
    ofTranslate(transform.position);
    ofRotateZ(transform.rotation);
    ofScale(transform.scale, transform.scale);
    ofNoFill();
    ofSetLineWidth(1);
    drawQuadTree(PhysicsManager::getQT());
    ofFill();
    ofPopMatrix();
}

void QuadTreeController::setup() {

}

void QuadTreeController::update(float dt) {

}
