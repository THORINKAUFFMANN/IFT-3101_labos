#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofSetupScreen();
	ofSetSmoothLighting(true);
	rotationX = 0.0f;
	rotationY = 0.0f;
	boxSize = 550.0f;
	lightWidth = 130.0f;
	lightDepth = 105.0f;
	
	// Configuration des cubes
	cube1.set(80, 100, 80);
	cube1.setResolution(2);
	
	cube2.set(60, 80, 100);
	cube2.setResolution(2);
	
	// Configuration de la lumière principale
	// Positionnée légèrement sous le rectangle lumineux au plafond
	light.setPosition(275, 540, 225);
	light.setDiffuseColor(ofColor(255, 255, 255));      // Blanc pur - intensité maximale
	light.setSpecularColor(ofColor(255, 255, 255));
	light.setAmbientColor(ofColor(100, 100, 100));      // Ambiance augmentée pour mieux éclairer
	light.setAttenuation(1.0f, 0.01f, 0.0001f);         // Atténuation réduite pour plus de portée
	
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
	
	// Dessiner la boîte Cornell
	drawCornellBox();
	
	// Dessiner le rectangle lumineux au plafond (source visuelle)
	ofDisableLighting();
	drawCeilingLight();
	ofEnableLighting();
	
	// Dessiner les cubes
	drawCubes();
	
	ofPopMatrix();
	
	// Désactiver la lumière pour l'affichage du texte
	light.disable();
	
	// Affichage des instructions
	ofSetColor(255);
	ofDrawBitmapString("Cornell Box avec lumiere de plafond", 10, 20);
	ofDrawBitmapString("Utilisez la souris pour faire tourner la boite", 10, 40);
}

//--------------------------------------------------------------
void ofApp::drawCornellBox() {
	float halfSize = boxSize / 2.0f;
	
	// Créer un matériau pour les surfaces
	ofMaterial material;
	material.setSpecularColor(ofColor(200, 200, 200));
	material.setShininess(32);
	
	// Mur gauche (Red) - position en X négative
	ofSetColor(200, 0, 0);
	material.setDiffuseColor(ofColor(200, 0, 0));
	material.setAmbientColor(ofColor(200, 0, 0));  // Augmenté pour meilleur éclairage
	material.begin();
	ofPushMatrix();
	ofTranslate(-halfSize, 0, 0);
	ofDrawBox(0, 0, 0, halfSize, boxSize, boxSize);
	ofPopMatrix();
	material.end();
	
	// Mur droit (Green) - position en X positive
	ofSetColor(0, 200, 0);
	material.setDiffuseColor(ofColor(0, 200, 0));
	material.setAmbientColor(ofColor(0, 200, 0));  // Augmenté pour meilleur éclairage
	material.begin();
	ofPushMatrix();
	ofTranslate(halfSize, 0, 0);
	ofDrawBox(0, 0, 0, halfSize, boxSize, boxSize);
	ofPopMatrix();
	material.end();
	
	// Mur arrière (White)
	ofSetColor(200, 200, 200);
	material.setDiffuseColor(ofColor(200, 200, 200));
	material.setAmbientColor(ofColor(200, 200, 200));  // Augmenté pour meilleur éclairage
	material.begin();
	ofPushMatrix();
	ofTranslate(0, 0, -halfSize);
	ofDrawBox(0, 0, 0, boxSize, boxSize, halfSize);
	ofPopMatrix();
	material.end();
	
	// Sol (White)
	ofSetColor(200, 200, 200);
	material.setDiffuseColor(ofColor(200, 200, 200));
	material.setAmbientColor(ofColor(200, 200, 200));  // Augmenté pour meilleur éclairage
	material.begin();
	ofPushMatrix();
	ofTranslate(0, halfSize, 0);
	ofDrawBox(0, 0, 0, boxSize, halfSize, boxSize);
	ofPopMatrix();
	material.end();
	
	// Plafond (White)
	ofSetColor(200, 200, 200);
	material.setDiffuseColor(ofColor(200, 200, 200));
	material.setAmbientColor(ofColor(200, 200, 200));  // Augmenté pour meilleur éclairage
	material.begin();
	ofPushMatrix();
	ofTranslate(0, -halfSize, 0);
	ofDrawBox(0, 0, 0, boxSize, halfSize, boxSize);
	ofPopMatrix();
	material.end();
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
void ofApp::drawCubes() {
	// Matériau pour les cubes
	ofMaterial cubeMaterial;
	cubeMaterial.setSpecularColor(ofColor(200, 200, 200));
	cubeMaterial.setShininess(64);
	
	// Premier cube - Cube rouge translucide
	ofPushMatrix();
	ofTranslate(-80, 50, 0);
	ofRotateDeg(30, 0, 1, 0);
	
	ofSetColor(220, 80, 80);
	cubeMaterial.setDiffuseColor(ofColor(220, 80, 80));
	cubeMaterial.setAmbientColor(ofColor(220, 80, 80));  // Augmenté pour meilleur éclairage
	cubeMaterial.begin();
	cube1.draw();
	cubeMaterial.end();
	
	ofPopMatrix();
	
	// Deuxième cube - Cube cyan/bleu
	ofPushMatrix();
	ofTranslate(100, 30, -50);
	ofRotateDeg(-25, 1, 0, 1);
	
	ofSetColor(80, 180, 220);
	cubeMaterial.setDiffuseColor(ofColor(80, 180, 220));
	cubeMaterial.setAmbientColor(ofColor(80, 180, 220));  // Augmenté pour meilleur éclairage
	cubeMaterial.begin();
	cube2.draw();
	cubeMaterial.end();
	
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawCeilingLight() {
	// Dessiner le rectangle blanc brillant au plafond
	ofPushMatrix();
	
	// Position du rectangle lumineux : centré en X, au plafond en Y, légèrement vers l'avant en Z
	float halfSize = boxSize / 2.0f;
	ofTranslate(-halfSize + 275, -halfSize + 549, -halfSize + 225);
	ofRotateXDeg(90); // Orienter horizontalement
	
	ofSetColor(255, 255, 255); // Blanc pur
	ofFill();
	ofDrawRectangle(-lightWidth / 2.0f, -lightDepth / 2.0f, lightWidth, lightDepth);
	
	ofPopMatrix();
}
