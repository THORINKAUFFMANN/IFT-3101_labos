#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofSetupScreen();
	rotationX = 0.0f;
	rotationY = 0.0f;
	boxSize = 500.0f;
	lightPlaneSize = 100.0f;
	
	// Configuration de la lumière
	light.setPosition(0, -boxSize/2 + 30, 0);
	light.setAmbientColor(ofColor(200, 200, 200));
	light.setDiffuseColor(ofColor(255, 255, 255));
	light.setSpecularColor(ofColor(255, 255, 255));
	
	// Activer l'éclairage
	ofEnableLighting();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(50, 50, 50);
	
	// Configuration de la caméra
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Activer la lumière
	light.enable();
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	ofRotateXDeg(rotationX);
	ofRotateYDeg(rotationY);
	
	drawCornellBox();
	
	ofPopMatrix();
	
	// Désactiver la lumière pour l'affichage du texte
	light.disable();
	
	// Affichage des instructions
	ofSetColor(255);
	ofDrawBitmapString("Boîte de Cornell avec éclairage", 10, 20);
	ofDrawBitmapString("Utilisez la souris pour faire tourner la boîte", 10, 40);
}

//--------------------------------------------------------------
void ofApp::drawCornellBox() {
	float halfSize = boxSize / 2.0f;
	
	// Créer un matériau pour les surfaces
	ofMaterial material;
	material.setSpecularColor(ofColor(200, 200, 200));
	material.setShininess(32);
	
	// Mur gauche (Red)
	ofSetColor(200, 0, 0);
	material.setDiffuseColor(ofColor(200, 0, 0));
	material.setAmbientColor(ofColor(100, 0, 0));
	material.begin();
	ofDrawBox(-halfSize, 0, 0, boxSize / 2, boxSize, boxSize);
	material.end();
	
	// Mur droit (Green)
	ofSetColor(0, 200, 0);
	material.setDiffuseColor(ofColor(0, 200, 0));
	material.setAmbientColor(ofColor(0, 100, 0));
	material.begin();
	ofDrawBox(halfSize, 0, 0, boxSize / 2, boxSize, boxSize);
	material.end();
	
	// Mur arrière (White)
	ofSetColor(200, 200, 200);
	material.setDiffuseColor(ofColor(200, 200, 200));
	material.setAmbientColor(ofColor(100, 100, 100));
	material.begin();
	ofDrawBox(0, 0, -halfSize, boxSize, boxSize, boxSize / 2);
	material.end();
	
	// Sol (White)
	ofSetColor(200, 200, 200);
	material.setDiffuseColor(ofColor(200, 200, 200));
	material.setAmbientColor(ofColor(100, 100, 100));
	material.begin();
	ofDrawBox(0, halfSize, 0, boxSize, boxSize / 2, boxSize);
	material.end();
	
	// Plafond (White)
	ofSetColor(200, 200, 200);
	material.setDiffuseColor(ofColor(200, 200, 200));
	material.setAmbientColor(ofColor(100, 100, 100));
	material.begin();
	ofDrawBox(0, -halfSize, 0, boxSize, boxSize / 2, boxSize);
	material.end();
	
	// Dessiner le plan lumineux dans le plafond
	drawLightPlane();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	rotationY += (x - ofGetPreviousMouseX()) * 0.5f;
	rotationX += (y - ofGetPreviousMouseY()) * 0.5f;
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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::drawLightPlane() {
	float halfSize = boxSize / 2.0f;
	
	// Désactiver l'éclairage temporairement pour que le plan soit visible
	light.disable();
	
	// Positionner le plan lumineux dans le plafond
	ofPushMatrix();
	ofTranslate(0, -halfSize + 2, 0);
	
	// Dessiner le plan lumineux en blanc/jaune clair
	ofSetColor(255, 255, 200);
	
	// Créer un petit plan carré
	ofBeginShape();
	float half = lightPlaneSize / 2.0f;
	ofVertex(-half, 0, -half);
	ofVertex(half, 0, -half);
	ofVertex(half, 0, half);
	ofVertex(-half, 0, half);
	ofEndShape(true);
	
	ofPopMatrix();
	
	// Réactiver l'éclairage
	light.enable();
}
