#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    std::string pathMesh = "./Skull/12140_Skull_v3_L2.obj";
    std::string pathTex = "./Skull/Skull.jpg";

    // try to load model
    bool modelLoaded = _model.loadModel(pathMesh);
    if(!modelLoaded){
        ofLogError("ofApp") << "Failed to load model: " << pathMesh;
        _loaded = false;
        return;
    }

    // load texture image
    if(!_texture.load(pathTex)){
        ofLogError("ofApp") << "Failed to load texture: " << pathTex;
        // still continue, model may have materials
    }else{
        // make sure texture is available for drawing
        _texture.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    }

    // enable normalized normals and scale to fit
    _model.setScaleNormalization(true);
    // apply a persistent initial rotation so the model is oriented before
    // the per-frame rotation in draw() is applied on top of it.
    // setRotation(index, degrees, x, y, z) — index 0 for the first transform
    _model.setRotation(0, 90.0f, 1.0f, 0.0f, 0.0f);
    _loaded = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(!_loaded) return;
    float dt = ofGetLastFrameTime();
    _angleDeg += _rotationSpeed * dt;
    if(_angleDeg >= 360.0f) _angleDeg -= 360.0f;
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(!_loaded) return;

    ofEnableDepthTest();
    ofBackground(30);

    // position camera-ish by translating to center
    ofPushMatrix();
    // center the model
    ofTranslate(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f, 45);

    // apply rotation around Y axis
    ofRotateDeg(_angleDeg, 0, 1, 0);

    // if we have a texture, bind it before drawing
    if(_texture.isAllocated()){
        _texture.getTexture().bind();
        _model.drawFaces();
        _texture.getTexture().unbind();
    }else{
        _model.drawFaces();
    }

    ofPopMatrix();
    ofDisableDepthTest();
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
