#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofSetupScreen();
	rotationX = 0.0f;
	rotationY = 0.0f;
	boxSize = 500.0f;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(50, 50, 50);
	
	// Configuration de la caméra
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	ofRotateXDeg(rotationX);
	ofRotateYDeg(rotationY);
	
	drawCornellBox();
	
	ofPopMatrix();
	
	// Affichage des instructions
	ofSetColor(255);
	ofDrawBitmapString("Boîte de Cornell", 10, 20);
	ofDrawBitmapString("Utilisez la souris pour faire tourner la boîte", 10, 40);
}

//--------------------------------------------------------------
void ofApp::drawCornellBox() {
	float halfSize = boxSize / 2.0f;
	
	// Mur gauche (Red)
	ofSetColor(200, 0, 0);
	ofDrawBox(-halfSize, 0, 0, boxSize / 2, boxSize, boxSize);
	
	// Mur droit (Green)
	ofSetColor(0, 200, 0);
	ofDrawBox(halfSize, 0, 0, boxSize / 2, boxSize, boxSize);
	
	// Mur arrière (White)
	ofSetColor(200, 200, 200);
	ofDrawBox(0, 0, -halfSize, boxSize, boxSize, boxSize / 2);
	
	// Mur avant (partiellement ouvert)
	// ofSetColor(180, 180, 180);
	
	// Sol (White)
	ofSetColor(200, 200, 200);
	ofDrawBox(0, halfSize, 0, boxSize, boxSize / 2, boxSize);
	
	// Plafond (White)
	ofSetColor(200, 200, 200);
	ofDrawBox(0, -halfSize, 0, boxSize, boxSize / 2, boxSize);
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
