#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Configuration de la fenêtre
	ofSetFrameRate(60);
	ofBackground(50, 50, 50);
	
	// Charger les shaders pour le cel shading
	celShader.load("shaders/celShading.vert", "shaders/celShading.frag");
	
	// Initialiser les objets 3D
	sphere.setRadius(120);
	sphere.setResolution(64); // Plus haute résolution pour une meilleure démo
	
	box.set(200, 200, 200);
	box.setResolution(32);
	
	icoSphere.setRadius(120);
	icoSphere.setResolution(5);
	
	// Paramètres d'éclairage et de rendu
	lightPosition = glm::vec3(200, 200, 200);
	objectColor = glm::vec3(0.8f, 0.2f, 0.2f); // Rouge
	celLevels = 3.0f; // Nombre de niveaux de luminosité
	
	// Paramètres de rotation
	rotationX = 0.0f;
	rotationY = 0.0f;
	selectedObject = 0; // Démarrer avec la sphère
	
	// Activer la lumière 3D pour la prévisualisation
	ofEnableLighting();
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){
	// Rotation automatique pour voir l'effet cel shading
	rotationX += 0.5f;
	rotationY += 0.3f;
	
	// Les shaders prennent en charge l'éclairage
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(50, 50, 50);
	
	// Configuration 3D
	ofEnableDepthTest();
	
	// Caméra
	ofCamera camera;
	camera.setPosition(0, 0, 350);
	camera.lookAt(glm::vec3(0, 0, 0));
	camera.begin();
	
	// Utiliser le shader cel shading
	celShader.begin();
	
	// Passer les uniforms au shader
	celShader.setUniform3f("lightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
	celShader.setUniform3f("viewPosition", 0, 0, 350);
	celShader.setUniform3f("objectColor", objectColor.x, objectColor.y, objectColor.z);
	celShader.setUniform1f("celLevels", celLevels);
	
	// Sauvegarder la matrice de transformation
	ofPushMatrix();
	ofRotateDeg(rotationX, 1, 0, 0);
	ofRotateDeg(rotationY, 0, 1, 0);
	
	// Dessiner l'objet sélectionné
	switch(selectedObject) {
		case 0:
			sphere.draw();
			break;
		case 1:
			box.draw();
			break;
		case 2:
			icoSphere.draw();
			break;
	}
	
	ofPopMatrix();
	
	celShader.end();
	
	// Dessiner la position de la lumière (jaune)
	ofSetColor(255, 255, 0);
	ofDrawSphere(lightPosition.x, lightPosition.y, lightPosition.z, 10);
	
	camera.end();
	
	ofDisableDepthTest();
	
	// Afficher les informations à l'écran (en 2D)
	ofSetColor(255, 255, 255);
	
	string info = "";
	info += "CEL SHADING DEMO\n\n";
	info += "Object: ";
	switch(selectedObject) {
		case 0: info += "Sphere (Press 1)\n"; break;
		case 1: info += "Box (Press 2)\n"; break;
		case 2: info += "Ico Sphere (Press 3)\n"; break;
	}
	info += "\nCel Levels: " + ofToString(celLevels, 1) + " (UP/DOWN)\n";
	info += "Light Position: (" + ofToString((int)lightPosition.x) + ", " 
		+ ofToString((int)lightPosition.y) + ", " + ofToString((int)lightPosition.z) + ")\n";
	info += "Light Control: A/D (X), W/S (Y), Q/E (Z)\n\n";
	info += "Color: ";
	switch((int)(objectColor.x * 10)) {
		case 8: info += "Red (Press R)\n"; break;
		case 2: info += "Green (Press G)\n"; break;
		case 0: info += "Blue (Press B)\n"; break;
	}
	info += "Use R, G, B to change color\n";
	info += "Press SPACE to reset\n";
	
	ofDrawBitmapString(info, 20, 20);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case '1':
			selectedObject = (selectedObject + 1) % 3;
			break;
		case '2':
			// Couleur rouge
			objectColor = glm::vec3(0.8f, 0.2f, 0.2f);
			break;
		case '3':
			// Couleur verte
			objectColor = glm::vec3(0.2f, 0.8f, 0.2f);
			break;
		case '4':
			// Couleur bleue
			objectColor = glm::vec3(0.2f, 0.2f, 0.8f);
			break;
		case 'w':
		case 'W':
			lightPosition.y += 10;
			break;
		case 's':
		case 'S':
			lightPosition.y -= 10;
			break;
		case 'a':
		case 'A':
			lightPosition.x -= 10;
			break;
		case 'd':
		case 'D':
			lightPosition.x += 10;
			break;
		case 'q':
		case 'Q':
			lightPosition.z -= 10;
			break;
		case 'e':
		case 'E':
			lightPosition.z += 10;
			break;
		case OF_KEY_UP:
			celLevels = std::min(celLevels + 0.5f, 10.0f);
			break;
		case OF_KEY_DOWN:
			celLevels = std::max(celLevels - 0.5f, 1.0f);
			break;
		case ' ':
			// Reset
			lightPosition = glm::vec3(200, 200, 200);
			objectColor = glm::vec3(0.8f, 0.2f, 0.2f);
			celLevels = 3.0f;
			rotationX = 0.0f;
			rotationY = 0.0f;
			selectedObject = 0;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
