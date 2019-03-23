#include "ofApp.h"
#include "core/GameManager.h"
#include "core/PhysicsManager.h"
#include "core/InputManager.h"
#include "core/EventManager.h"
#include "core/DataLoader.h"

ofApp::ofApp() {
}

ofApp::~ofApp() {
}

//--------------------------------------------------------------
void ofApp::setup(){	
    ofSetBackgroundColor(ofColor::black);
    DataLoader::loadImages();
	InputManager::load();
	GameManager::instance().setup();
}

//--------------------------------------------------------------
void ofApp::update(){	
	GameManager::instance().update();
    PhysicsManager::update();
    GameManager::instance().destroy();
	InputManager::update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	GameManager::instance().draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    DataLoader::unloadImages();
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
