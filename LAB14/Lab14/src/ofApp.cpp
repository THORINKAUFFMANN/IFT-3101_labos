#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Configuration de la perspective
	ofSetupScreen();
	
	// Activation de la lumière pour mieux voir les sphères
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	
	// Initialisation du tableau des touches
	for (int i = 0; i < 256; i++) {
		keysPressed[i] = false;
	}
	
	// Initialisation de la caméra
	lastMouseX = ofGetMouseX();
	lastMouseY = ofGetMouseY();
}

//--------------------------------------------------------------
void ofApp::update(){
	// Mise à jour des rotations et orbites
	earthRotation += earthRotationSpeed;
	moonOrbitAngle += moonOrbitSpeed;
	moonRotation += moonRotationSpeed;
	
	// Normaliser les angles pour éviter l'overflow
	if (earthRotation > 360.0f) earthRotation -= 360.0f;
	if (moonOrbitAngle > 360.0f) moonOrbitAngle -= 360.0f;
	if (moonRotation > 360.0f) moonRotation -= 360.0f;
	
	// Gestion du déplacement à la caméra avec les flèches
	// Flèche haut/bas : déplacement avant/arrière
	if (keysPressed[OF_KEY_UP]) {
		cameraPos.z -= moveSpeed * cos(cameraAngleY);
		cameraPos.x -= moveSpeed * sin(cameraAngleY);
	}
	if (keysPressed[OF_KEY_DOWN]) {
		cameraPos.z += moveSpeed * cos(cameraAngleY);
		cameraPos.x += moveSpeed * sin(cameraAngleY);
	}
	
	// Flèche gauche/droite : déplacement latéral
	if (keysPressed[OF_KEY_LEFT]) {
		cameraPos.x -= moveSpeed * cos(cameraAngleY);
		cameraPos.z += moveSpeed * sin(cameraAngleY);
	}
	if (keysPressed[OF_KEY_RIGHT]) {
		cameraPos.x += moveSpeed * cos(cameraAngleY);
		cameraPos.z -= moveSpeed * sin(cameraAngleY);
	}
	
	// W/S pour monter/descendre
	if (keysPressed['z'] || keysPressed['Z']) {
		cameraPos.y += moveSpeed;
	}
	if (keysPressed['s'] || keysPressed['S']) {
		cameraPos.y -= moveSpeed;
	}
	
	// A/D pour déplacer la scène à gauche/droite
	if (keysPressed['a'] || keysPressed['A']) {
		sceneOffset.x -= moveSpeed;
	}
	if (keysPressed['d'] || keysPressed['D']) {
		sceneOffset.x += moveSpeed;
	}
	
	// Q/E pour déplacer la scène vers le haut/bas
	if (keysPressed['q'] || keysPressed['Q']) {
		sceneOffset.y += moveSpeed;
	}
	if (keysPressed['e'] || keysPressed['E']) {
		sceneOffset.y -= moveSpeed;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Fond noir pour l'espace
	ofBackground(10, 10, 20);
	
	// Configuration de la caméra
	ofPushMatrix();
	
	// Caméra avec mouvement libre + orbite
	float camX = cameraPos.x + cameraDistance * sin(cameraAngleY) * cos(cameraAngleX);
	float camY = cameraPos.y + cameraDistance * sin(cameraAngleX);
	float camZ = cameraPos.z + cameraDistance * cos(cameraAngleY) * cos(cameraAngleX);
	
	gluLookAt(camX, camY, camZ,                  // Position de la caméra
	          cameraPos.x, cameraPos.y, cameraPos.z,  // Point visé
	          0, 1, 0);                           // Vecteur "haut"
	
	// Affichage du repère
	ofSetColor(255, 0, 0);
	ofDrawLine(0, 0, 0, 100, 0, 0);  // Axe X en rouge
	ofSetColor(0, 255, 0);
	ofDrawLine(0, 0, 0, 0, 100, 0);  // Axe Y en vert
	ofSetColor(0, 0, 255);
	ofDrawLine(0, 0, 0, 0, 0, 100);  // Axe Z en bleu
	
	// Application du décalage de scène
	ofTranslate(sceneOffset.x, sceneOffset.y, sceneOffset.z);
	
	// Dessin de la Terre
	ofSetColor(100, 150, 255);  // Bleu
	ofPushMatrix();
	ofTranslate(earthPos.x, earthPos.y, earthPos.z);
	ofRotateYDeg(earthRotation);
	ofDrawSphere(earthRadius);
	ofPopMatrix();
	
	// Dessin de l'orbite de la Lune (cercle blanc pointillé)
	ofSetColor(200, 200, 200);
	ofPushMatrix();
	ofTranslate(earthPos.x, earthPos.y, earthPos.z);
	ofRotateXDeg(0);
	ofNoFill();
	ofDrawCircle(0, 0, moonOrbitRadius);
	ofFill();
	ofPopMatrix();
	
	// Calcul de la position de la Lune autour de la Terre
	float moonX = earthPos.x + moonOrbitRadius * cos(glm::radians(moonOrbitAngle));
	float moonY = earthPos.y;
	float moonZ = earthPos.z + moonOrbitRadius * sin(glm::radians(moonOrbitAngle));
	
	// Dessin de la Lune
	ofSetColor(220, 220, 220);  // Gris clair
	ofPushMatrix();
	ofTranslate(moonX, moonY, moonZ);
	ofRotateYDeg(moonRotation);
	ofDrawSphere(moonRadius);
	ofPopMatrix();
	
	// Affichage des informations
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("Terre-Lune Simulation", 10, 20);
	ofDrawBitmapString("Souris: Faire tourner la camera", 10, 40);
	ofDrawBitmapString("Fleches: Deplacer la camera", 10, 60);
	ofDrawBitmapString("W/S: Monter/Descendre", 10, 80);
	ofDrawBitmapString("A/D: Deplacer scene gauche/droite", 10, 100);
	ofDrawBitmapString("Q/E: Deplacer scene haut/bas", 10, 120);
	ofDrawBitmapString("Molette: Zoomer", 10, 140);
	ofDrawBitmapString("Espace: Pause/Reprendre", 10, 160);
	ofDrawBitmapString("R: Reinitialiser", 10, 180);
	ofDrawBitmapString("Distance camera: " + ofToString(cameraDistance), 10, 200);
	ofDrawBitmapString("Position camera: (" + ofToString((int)cameraPos.x) + ", " + 
	                    ofToString((int)cameraPos.y) + ", " + ofToString((int)cameraPos.z) + ")", 10, 220);
	
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// Enregistrer la touche pressée
	if (key < 256) {
		keysPressed[key] = true;
	}
	
	// Espace pour mettre en pause/reprendre la rotation
	if (key == ' ') {
		earthRotationSpeed = (earthRotationSpeed == 0) ? 0.5f : 0.0f;
		moonOrbitSpeed = (moonOrbitSpeed == 0) ? 0.01f : 0.0f;
		moonRotationSpeed = (moonRotationSpeed == 0) ? 0.1f : 0.0f;
	}
	// R pour réinitialiser la caméra
	if (key == 'r' || key == 'R') {
		cameraDistance = 400.0f;
		cameraAngleX = 0.0f;
		cameraAngleY = 0.0f;
		cameraPos = glm::vec3(0, 0, 0);
		sceneOffset = glm::vec3(0, 0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// Désenregistrer la touche relâchée
	if (key < 256) {
		keysPressed[key] = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (isMouseDragging) {
		// Calcul du delta
		int deltaX = x - lastMouseX;
		int deltaY = y - lastMouseY;
		
		// Mise à jour des angles de la caméra
		cameraAngleY += deltaX * 0.01f;
		cameraAngleX += deltaY * 0.01f;
		
		// Limiter l'angle X pour éviter de basculer complètement
		if (cameraAngleX > glm::pi<float>() / 2.0f) {
			cameraAngleX = glm::pi<float>() / 2.0f;
		}
		if (cameraAngleX < -glm::pi<float>() / 2.0f) {
			cameraAngleX = -glm::pi<float>() / 2.0f;
		}
		
		// Normaliser cameraAngleY
		if (cameraAngleY > glm::two_pi<float>()) {
			cameraAngleY -= glm::two_pi<float>();
		}
	}
	
	lastMouseX = x;
	lastMouseY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	isMouseDragging = true;
	lastMouseX = x;
	lastMouseY = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	isMouseDragging = false;
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
	// Scrolling vers le haut = zoom avant (diminue la distance)
	cameraDistance -= scrollY * 20.0f;
	
	// Limiter la distance pour ne pas entrer dans les objets
	if (cameraDistance < 100.0f) {
		cameraDistance = 100.0f;
	}
	if (cameraDistance > 1000.0f) {
		cameraDistance = 1000.0f;
	}
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
