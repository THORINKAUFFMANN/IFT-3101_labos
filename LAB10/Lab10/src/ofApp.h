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
		// Caméra
		ofCamera camera;
		
		// Lumières
		ofLight pointLight1;      // Point light
		ofLight pointLight2;      // Point light
		ofLight directionLight;   // Directional light
		ofLight spotLight;        // Spot light
		
		// Angles de rotation pour lumières dynamiques
		float pointLight1Angle;
		float pointLight2Angle;
		float spotLightAngle;
		
		// Matériau
		ofMaterial material;
		
		// Géométries de la scène
		ofIcoSpherePrimitive sphere;
		ofPlanePrimitive plane;
		ofBoxPrimitive box;
		
		// Paramètres de contrôle
		bool showLights;
		bool enableDynamicLighting;
};
