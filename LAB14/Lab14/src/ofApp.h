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
		// Paramètres de la Terre
		float earthRadius = 50.0f;
		glm::vec3 earthPos = glm::vec3(0, 0, 0);
		float earthRotation = 0.0f;
		
		// Paramètres de la Lune
		float moonRadius = 15.0f;
		float moonOrbitRadius = 150.0f;
		float moonOrbitAngle = 0.0f;
		float moonRotation = 0.0f;
		
		// Caméra interactive
		float cameraDistance = 400.0f;
		float cameraAngleX = 0.0f;
		float cameraAngleY = 0.0f;
		glm::vec3 cameraPos = glm::vec3(0, 0, 0);  // Position additionnelle pour déplacement libre
		glm::vec3 sceneOffset = glm::vec3(0, 0, 0);  // Décalage de la scène entière
		bool isMouseDragging = false;
		int lastMouseX = 0;
		int lastMouseY = 0;
		
		// Touches clavier pressées
		bool keysPressed[256];
		float moveSpeed = 5.0f;
		
		// Vitesses de rotation
		float earthRotationSpeed = 0.5f;
		float moonOrbitSpeed = 0.1f;
		float moonRotationSpeed = 0.1f;
};
