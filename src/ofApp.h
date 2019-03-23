#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
		ofApp();
		~ofApp();
        virtual void setup() override;
        virtual void update() override;
        virtual void draw() override;
        virtual void exit() override;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
        virtual void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
