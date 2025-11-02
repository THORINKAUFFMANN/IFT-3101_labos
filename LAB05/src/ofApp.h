#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"


class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
		
		private:
			// model loader and texture. References are unsafe here because
			// they must be initialized in a constructor - use concrete members instead.
			ofxAssimpModelLoader _model;
			ofImage _texture;
			bool _loaded = false;

			// rotation state
			float _angleDeg = 90.0f; // start rotated 90 degrees
			float _rotationSpeed = 30.0f; // degrees per second

			// interactive camera so user can move while model rotates
			ofEasyCam _cam;
};
