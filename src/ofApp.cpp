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
<<<<<<< HEAD

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

=======
	InputManager::setKeyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    EventManager::onMouseMove(x, y);
>>>>>>> 637f5fcb32c858b824737766c171e085cae44958
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
<<<<<<< HEAD

=======
    EventManager::onMouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    EventManager::onMouseScrolled(x, y, scrollX, scrollY);
>>>>>>> 637f5fcb32c858b824737766c171e085cae44958
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
<<<<<<< HEAD

=======
    InputManager::setKeyPressed(button);
    EventManager::onMousePressed(x, y);
>>>>>>> 637f5fcb32c858b824737766c171e085cae44958
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
<<<<<<< HEAD

=======
    InputManager::setKeyReleased(button);
    EventManager::onMouseReleased(x, y);
>>>>>>> 637f5fcb32c858b824737766c171e085cae44958
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
<<<<<<< HEAD
void ofApp::windowResized(int w, int h){

=======
void ofApp::windowResized(int w, int h){    
    EventManager::onWindowResized(w, h);
>>>>>>> 637f5fcb32c858b824737766c171e085cae44958
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
