#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Enable 3D
    ofEnableDepthTest();
    
    // Set up the primitives
    box.set(100);
    box.setPosition(-100, 50, 0);
    
    sphere.setRadius(50);
    
    cylinder.set(50, 120);
    cylinder.setPosition(50, 100, 0);
    
    cone.set(50, 100);
    cone.setPosition(50, -100, 0);
    
    // Initial camera setup
    cameraPosition = glm::vec3(0, 0, 800);  // Start position
    camera.setPosition(cameraPosition);
    camera.lookAt(glm::vec3(0, 0, 0));
    cameraMoveSpeed = 10.0f;  // Adjust this to change movement speed
    camera.disableMouseInput();
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update camera position based on keyboard input
    if(keyStates[OF_KEY_LEFT]) {
        cameraPosition.x -= cameraMoveSpeed;
    }
    if(keyStates[OF_KEY_RIGHT]) {
        cameraPosition.x += cameraMoveSpeed;
    }
    if(keyStates[OF_KEY_UP]) {
        cameraPosition.y -= cameraMoveSpeed;
    }
    if(keyStates[OF_KEY_DOWN]) {
        cameraPosition.y += cameraMoveSpeed;
    }
    
    // Update camera position and keep looking at center
    camera.setPosition(cameraPosition);
    camera.lookAt(glm::vec3(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    camera.begin();
    
    // Draw the box
    ofSetColor(200, 100, 100);
    box.draw();

    ofSetColor(100, 200, 100);
    sphere.draw();

    ofSetColor(200, 100, 200);
    cylinder.draw();

    ofSetColor(200, 200, 100);
    cone.draw();
    
    camera.end();
    
    // Draw camera position text at the top of the window
    ofSetColor(255, 255, 255);  // White text
    string posText = "Camera Position - X: " + ofToString(cameraPosition.x, 1) + 
                                  " Y: " + ofToString(cameraPosition.y, 1) + 
                                  " Z: " + ofToString(cameraPosition.z, 1);
    ofDrawBitmapString(posText, 10, 20);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    keyStates[key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    keyStates[key] = false;
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


