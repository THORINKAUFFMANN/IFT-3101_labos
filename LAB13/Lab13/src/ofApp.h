#pragma once

#include "ofMain.h"

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
		// Shader pour le cel shading
		ofShader celShader;
		
		// Objets 3D
		ofSpherePrimitive sphere;
		ofBoxPrimitive box;
		ofIcoSpherePrimitive icoSphere;
		
		// Paramètres d'éclairage
		glm::vec3 lightPosition;
		glm::vec3 objectColor;
		
		// Paramètres d'interaction
		float celLevels;
		float rotationX, rotationY;
		int selectedObject; // 0 = sphere, 1 = box, 2 = icoSphere
		
};
