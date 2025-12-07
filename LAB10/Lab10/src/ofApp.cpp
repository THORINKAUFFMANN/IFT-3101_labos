#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Configuration du rendu 3D
	ofEnableDepthTest();
	ofSetBackgroundColor(20, 20, 30);
	
	// Initialisation de la caméra
	camera.setPosition(0, 100, 300);
	camera.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	camera.setFarClip(10000);
	
	// Configuration du matériau avec réflexion ambiante, diffuse et spéculaire
	material.setAmbientColor(ofColor(100, 100, 100, 255));
	material.setDiffuseColor(ofColor(200, 150, 100, 255));
	material.setSpecularColor(ofColor(255, 255, 255, 255));
	material.setShininess(64.0f);
	
	// Configuration des lumières point
	pointLight1.setPosition(150, 150, 150);
	pointLight1.setAttenuation(1, 0.01, 0.0001);
	pointLight1.setAmbientColor(ofColor(50, 50, 50));
	pointLight1.setDiffuseColor(ofColor(255, 100, 100)); // Rouge
	pointLight1.setSpecularColor(ofColor(255, 255, 255));
	
	pointLight2.setPosition(-150, 150, -150);
	pointLight2.setAttenuation(1, 0.01, 0.0001);
	pointLight2.setAmbientColor(ofColor(50, 50, 50));
	pointLight2.setDiffuseColor(ofColor(100, 100, 255)); // Bleu
	pointLight2.setSpecularColor(ofColor(255, 255, 255));
	
	// Configuration de la lumière directionnelle
	directionLight.setDirectional();
	directionLight.setOrientation(glm::vec3(45, 45, 0));
	directionLight.setAmbientColor(ofColor(80, 80, 80));
	directionLight.setDiffuseColor(ofColor(200, 200, 200)); // Blanc
	directionLight.setSpecularColor(ofColor(255, 255, 255));
	
	// Configuration du spot light
	spotLight.setSpotlight();
	spotLight.setPosition(0, 200, 100);
	spotLight.setOrientation(glm::vec3(0, -1, -0.5));
	spotLight.setSpotConcentration(50.0f);
	spotLight.setSpotlightCutOff(30.0f);
	spotLight.setAttenuation(1, 0.01, 0.0001);
	spotLight.setAmbientColor(ofColor(30, 30, 30));
	spotLight.setDiffuseColor(ofColor(100, 255, 100)); // Vert
	spotLight.setSpecularColor(ofColor(255, 255, 255));
	
	// Initialisation des angles de rotation
	pointLight1Angle = 0;
	pointLight2Angle = 0;
	spotLightAngle = 0;
	
	// Initialisation des géométries
	sphere.set(80, 4);
	plane.set(400, 400, 20, 20);
	box.set(100, 100, 100);
	
	// Paramètres de contrôle
	showLights = false;
	enableDynamicLighting = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	if(enableDynamicLighting) {
		// Mise à jour des angles de rotation
		pointLight1Angle += 1.5f;
		pointLight2Angle += 2.0f;
		spotLightAngle += 0.8f;
		
		// Positions dynamiques des lumières point autour de la scène
		float radius1 = 200;
		pointLight1.setPosition(
			cos(glm::radians(pointLight1Angle)) * radius1,
			150 + 50 * sin(glm::radians(pointLight1Angle * 0.5f)),
			sin(glm::radians(pointLight1Angle)) * radius1
		);
		
		float radius2 = 220;
		pointLight2.setPosition(
			cos(glm::radians(pointLight2Angle + 180)) * radius2,
			100 + 80 * sin(glm::radians(pointLight2Angle * 0.3f)),
			sin(glm::radians(pointLight2Angle + 180)) * radius2
		);
		
		// Position dynamique du spot light
		spotLight.setPosition(0, 250, 150 * cos(glm::radians(spotLightAngle)));
		spotLight.setOrientation(glm::normalize(glm::vec3(0, -1, -0.3f)));
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();
	
	// Activation des lumières
	pointLight1.enable();
	pointLight2.enable();
	directionLight.enable();
	spotLight.enable();
	
	// Application du matériau
	material.begin();
	
	// Dessiner le plan au sol
	ofPushMatrix();
	ofTranslate(0, 0, 0);
	ofRotateXDeg(90);
	plane.draw();
	ofPopMatrix();
	
	// Dessiner la sphère
	ofPushMatrix();
	ofTranslate(0, 100, 0);
	sphere.draw();
	ofPopMatrix();
	
	// Dessiner les boîtes
	ofPushMatrix();
	ofTranslate(150, 50, 150);
	box.draw();
	ofPopMatrix();
	
	ofPushMatrix();
	ofTranslate(-150, 50, -150);
	box.draw();
	ofPopMatrix();
	
	// Fin du matériau
	material.end();
	
	// Dessiner les positions des lumières si activé
	if(showLights) {
		ofDisableLighting();
		
		// Spot de la lumière point 1
		ofSetColor(255, 100, 100);
		ofDrawSphere(pointLight1.getPosition(), 10);
		
		// Spot de la lumière point 2
		ofSetColor(100, 100, 255);
		ofDrawSphere(pointLight2.getPosition(), 10);
		
		// Spot du spot light
		ofSetColor(100, 255, 100);
		ofDrawSphere(spotLight.getPosition(), 10);
		
		ofEnableLighting();
	}
	
	// Désactiver les lumières
	pointLight1.disable();
	pointLight2.disable();
	directionLight.disable();
	spotLight.disable();
	
	camera.end();
	
	// Affichage des informations
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("Lab 10 - Lumières Dynamiques", 10, 20);
	ofDrawBitmapString("Press 'L' to toggle light indicators", 10, 40);
	ofDrawBitmapString("Press 'D' to toggle dynamic lighting", 10, 60);
	ofDrawBitmapString("FPS: " + std::to_string(ofGetFrameRate()), 10, 80);
	
	if(showLights) {
		ofDrawBitmapString("Light indicators: ON", 10, 100);
	} else {
		ofDrawBitmapString("Light indicators: OFF", 10, 100);
	}
	
	if(enableDynamicLighting) {
		ofDrawBitmapString("Dynamic lighting: ON", 10, 120);
	} else {
		ofDrawBitmapString("Dynamic lighting: OFF", 10, 120);
	}
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'l' || key == 'L') {
		showLights = !showLights;
	}
	if(key == 'd' || key == 'D') {
		enableDynamicLighting = !enableDynamicLighting;
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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
