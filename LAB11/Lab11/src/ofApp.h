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
		// Mesh pour la surface avec déformation de relief
		ofMesh reliefMesh;
		
		// Texture de heightmap
		ofImage heightMapTexture;
		
		// Texture couleur
		ofImage colorTexture;
		
		// Variables de contrôle
		glm::vec3 lightPosition;
		float bumpIntensity;
		float rotation;
		float rotationX;
		float rotationY;
		float rotationZ;
		int meshResolution;
		bool useColorTexture;
		
		// Méthodes utilitaires
		void generateReliefMesh();
		void generateHeightMapTexture();
		void loadColorTexture();
		
};
