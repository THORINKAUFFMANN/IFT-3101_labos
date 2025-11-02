#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Configuration de la fenêtre
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    // Activation de l'éclairage
    ofEnableLighting();
    
    // Configuration de la lumière
    light.setPointLight();
    light.setPosition(0, 500, 500);
    light.setDiffuseColor(ofColor(255, 255, 255));
    
    // Configuration des cubes
    cubeSize = 50;
    // Création de plusieurs cubes à différentes positions
    for(int i = 0; i < 20; i++) {
        float x = ofRandom(-500, 500);
        float y = ofRandom(-500, 500);
        float z = ofRandom(-1000, 0);
        cubePositions.push_back(ofVec3f(x, y, z));
    }
    
    // Initialisation des paramètres de la caméra
    initialZ = 500;  // Plus proche au début
    targetZ = 1500;  // Distance finale réduite
    initialFOV = 60;
    targetFOV = 30;
    
    // Configuration de l'animation
    isVertigoActive = false;
    animationTime = 0;
    animationDuration = 5.0f; // 5 secondes pour un effet plus dramatique
    
    // Position initiale de la caméra
    cameraZ = initialZ;
    fov = initialFOV;
    camera.setFov(fov);
    
    // Configuration de la caméra
    camera.setNearClip(10);
    camera.setFarClip(10000);
    camera.disableMouseInput();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(isVertigoActive) {
        // Mise à jour du temps d'animation
        animationTime += ofGetLastFrameTime();
        
        if(animationTime >= animationDuration) {
            // Fin de l'animation
            isVertigoActive = false;
            animationTime = 0;
            
            // Réinitialisation des paramètres
            cameraZ = initialZ;
            fov = initialFOV;
        } else {
            // Calcul de l'interpolation (ease in-out)
            float t = animationTime / animationDuration;
            float smoothT = 0.5f - cos(t * PI) * 0.5f;
            
            // Application de l'interpolation sur la position Z et le FOV
            cameraZ = ofLerp(initialZ, targetZ, smoothT);
            fov = ofLerp(initialFOV, targetFOV, smoothT);
        }
        
        // Mise à jour des paramètres de la caméra
        camera.setFov(fov);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofEnableLighting();
    ofEnableDepthTest();
    
    camera.begin();
    
    // Translation de la caméra sur l'axe Z
    ofTranslate(0, 0, -cameraZ);
    
    // Activation de la lumière
    light.enable();
    
    // Dessin des cubes
    for(const auto& pos : cubePositions) {
        ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateXDeg(ofGetElapsedTimef() * 20);
        ofRotateYDeg(ofGetElapsedTimef() * 30);
        ofDrawBox(cubeSize);
        ofPopMatrix();
    }
    
    // Désactivation de la lumière
    light.disable();
    
    camera.end();
    
    // Affichage des informations à l'écran
    ofSetColor(255);
    string info = "Appuyez sur ESPACE pour activer l'effet vertigo\n";
    info += "Position Z: " + ofToString(cameraZ, 0) + "\n";
    info += "FOV: " + ofToString(fov, 1);
    ofDrawBitmapString(info, 20, 20);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ' && !isVertigoActive) {
        // Activer l'effet vertigo
        isVertigoActive = true;
        animationTime = 0;
        
        // Inverser les positions initiales et finales pour l'effet de va-et-vient
        float tempZ = initialZ;
        initialZ = targetZ;
        targetZ = tempZ;
        
        float tempFOV = initialFOV;
        initialFOV = targetFOV;
        targetFOV = tempFOV;
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
