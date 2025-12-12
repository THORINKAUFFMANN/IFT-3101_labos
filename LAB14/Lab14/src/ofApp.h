#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
private:
    // Caméra
    ofEasyCam cam;
    
    // Textures
    ofImage diffuseTexture;
    ofImage normalTexture;
    
    // Lumières
    ofLight pointLight;
    ofLight directionalLight;
    
    // Matériaux
    ofMaterial material;
    
    // Mesh
    ofSpherePrimitive sphere;
    ofBoxPrimitive box;
    ofConePrimitive cone;
    
    // Paramètres d'illumination
    float ambientStrength;
    float specularPower;
    bool useTexture;
    bool useNormalMap;
    
    // Rotation
    float rotation;
    
    // Shader pour normal mapping
    ofShader normalMapShader;
    
    void setupLights();
    void setupMaterials();
    void setupShader();
    void drawScene();
    void drawTexturedSphere();
    void createProceduralTexture();
};