#include "ofApp.h"

#include "core/ScenePlayer.h"
#include "core/GameRenderer.h"
#include "core/PhysicsManager.h"
#include "core/InputManager.h"
#include "core/EventManager.h"
#include "core/DataManager.h"
#include "core/Timer.h"

#include "dummy/Scene.h"

ofApp::ofApp() {
}

ofApp::~ofApp() {
}

//--------------------------------------------------------------
void ofApp::setup() {	
    ofSetVerticalSync(true);
    ofSetBackgroundColor(ofColor::black);
	ofEnableAlphaBlending();
    InputManager::setup();
    DataManager::load();	
    ScenePlayer::loadScene(new Scene());
    GameRenderer::setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	Timer::update();

	if (ScenePlayer::loadingScene) {
		ScenePlayer::showNextScene();
		GameRenderer::reset();
	}
	ScenePlayer::instance().update(Timer::deltaTime());
    PhysicsManager::update(Timer::deltaTime());
	InputManager::update();
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::draw() {
    GameRenderer::draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    DataManager::unload();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {	
	InputManager::setKeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	InputManager::setKeyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    EventManager::onMouseMove(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    EventManager::onMouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    EventManager::onMouseScrolled(x, y, scrollX, scrollY);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    InputManager::setKeyPressed(button);
    EventManager::onMousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    InputManager::setKeyReleased(button);
    EventManager::onMouseReleased(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {    
    EventManager::onWindowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}
