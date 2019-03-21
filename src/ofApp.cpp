#include "ofApp.h"
#include "GameManager.h"
#include "Input.h"

ofApp::ofApp() {
}

ofApp::~ofApp() {
}

//--------------------------------------------------------------
void ofApp::setup(){	
	Input::load();
	GameManager::instance().setup();
}

//--------------------------------------------------------------
void ofApp::update(){	
	GameManager::instance().update();
	Input::update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	GameManager::instance().draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	std::cout << "key pressed:" << key << std::endl;
	Input::setKeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	Input::setKeyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
