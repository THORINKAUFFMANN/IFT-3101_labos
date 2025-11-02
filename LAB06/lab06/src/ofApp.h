#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		// Modèles 3D
		ofNode sceneNode;      // Node pour la scène
		ofNode moonNode;       // Node pour la lune
        ofMesh sceneMesh;      // Mesh de la scène
        ofMesh moonMesh;       // Mesh de la lune
        ofTexture sceneTexture; // Texture de la scène
        ofTexture moonTexture;  // Texture de la lune
		
		// Lumières
		ofLight mainLight;     // Lumière principale
		ofLight moonLight;     // Lumière pour la lune
		// Lumière
ofLight light;

// Cubes
vector<ofVec3f> cubePositions;
float cubeSize;
		// Caméra
		ofEasyCam camera;
		float cameraZ;         // Position Z de la caméra
		float fov;            // Champ de vision (Field of View)
		
		// Animation
		bool isVertigoActive;   // État de l'effet vertigo
		float animationTime;    // Temps écoulé de l'animation
		float animationDuration;// Durée totale de l'animation
		
		// Paramètres de l'effet
		float initialZ;        // Position Z initiale
		float targetZ;         // Position Z finale
		float initialFOV;      // FOV initial
		float targetFOV;       // FOV final
		
		// Paramètres des objets
		float sceneScale;      // Échelle de la scène
		float moonScale;       // Échelle de la lune
		ofVec3f moonPosition;  // Position de la lune

        // Chargement des modèles
        void loadScene();     // Fonction pour charger la scène
        void loadMoon();      // Fonction pour charger la lune
        void setupLights();   // Configuration des lumières

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
		
};
