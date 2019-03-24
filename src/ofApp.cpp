#include "ofApp.h"
#include "core/GameManager.h"
#include "core/GameRenderer.h"
#include "core/PhysicsManager.h"
#include "core/InputManager.h"
#include "core/EventManager.h"
#include "core/DataManager.h"

ofApp::ofApp() {
}

ofApp::~ofApp() {
}

//--------------------------------------------------------------
void ofApp::setup(){	
    ofSetBackgroundColor(ofColor::black);
    InputManager::setup();
    DataManager::load();	
	GameManager::instance().setup();
    GameRenderer::setup();
}

//--------------------------------------------------------------
void ofApp::update(){	
    auto dt = ofGetLastFrameTime();
	GameManager::instance().update(dt);
    PhysicsManager::update(dt);
	InputManager::update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    GameRenderer::draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    DataManager::unload();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){	
	InputManager::setKeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	InputManager::setKeyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    EventManager::onMouseMove(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    EventManager::onMouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    EventManager::onMouseScrolled(x, y, scrollX, scrollY);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    InputManager::setKeyPressed(button);
    EventManager::onMousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    InputManager::setKeyReleased(button);
    EventManager::onMouseReleased(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){    
    EventManager::onWindowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
