#include "ofApp.h"
#include <stack>

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetLineWidth(2);
     // --- L-system setup ---
    axiom = "X";
    current = axiom;
    this->_iterations = 15;
    this->_angle = 90;
    std::cout << this->_iterations << std::endl;

    rules.clear();
    rules['F'] = "FF";
    rules['X'] = "F+[[X]-X]-F[-FX]+X";

    for(int i = 0; i < 6; i++){
        generate();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/2, ofGetHeight()); // start bottom-center
    drawBranch(current, 10, this->_angle); // step length = 5, angle = 25 degrees
}

//--------------------------------------------------------------
void ofApp::generate(){
    string next;
    for(char c : current){
        if(rules.find(c) != rules.end()){
            next += rules[c];
        } else {
            next += c; // keep as is
        }
    }
    current = next;
}

//--------------------------------------------------------------
void ofApp::drawBranch(string commands, float length, float angle){
    std::stack<ofMatrix4x4> transformStack;
    float curAngle = -90; // start pointing up

    for(char c : commands){
        switch(c){
            case 'F':
                {
                    float rad = ofDegToRad(curAngle);
                    ofDrawLine(0, 0, cos(rad) * length, sin(rad) * length);
                    ofTranslate(cos(rad) * length, sin(rad) * length);
                }
                break;
            case '+':
                curAngle += angle;
                break;
            case '-':
                curAngle -= angle;
                break;
            case '[':
                transformStack.push(ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
                break;
            case ']':
                if(!transformStack.empty()){
                    ofLoadMatrix(transformStack.top());
                    transformStack.pop();
                }
                break;
            default:
                break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    std::cout << key;
    switch (key) {
        case 57358:
        this->_iterations += 1;
            std::cout << ": " << this->_iterations << ": " << this->_angle << std::endl;
            ofClear(0, 0, 0);
            // for(int i=0; i<this->_iterations; i++){
            //     generate();
            // }
            break;
        case 57356:
            this->_iterations -= 1;
            std::cout << ": " << this->_iterations << ": " << this->_angle << std::endl;
            ofClear(0, 0, 0);
            // for(int i=0; i<this->_iterations; i++){
            //     generate();
            // }
        default:
            break;
        case 57357:
            this->_angle -= 10;
            std::cout << ": " << this->_iterations << ": " << this->_angle << std::endl;
            ofClear(0, 0, 0);
            for(int i=0; i<this->_iterations; i++){
                generate();
            }
        case 57359:
            this->_angle += 10;
            std::cout << ": " << this->_iterations << ": " << this->_angle << std::endl;
            ofClear(0, 0, 0);
            for(int i=0; i<this->_iterations; i++){
                generate();
            }
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
