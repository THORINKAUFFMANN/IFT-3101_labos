#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    // Initialisation des paramètres
    ambientStrength = 0.2;
    specularPower = 32.0;
    useTexture = true;
    useNormalMap = false;
    rotation = 0;
    
    // Configuration des primitives
    sphere.set(100, 50);
    box.set(80);
    cone.set(60, 120, 10, 3);
    
    // Chargement des textures
    diffuseTexture.load("texture.jpg"); // Remplacer par votre texture
    // Si vous n'avez pas de texture, créez-en une procédurale :
    if (!diffuseTexture.isAllocated()) {
        createProceduralTexture();
    }
    
    setupLights();
    setupMaterials();
    setupShader();
}

//--------------------------------------------------------------
void ofApp::createProceduralTexture() {
    int w = 512, h = 512;
    ofPixels pixels;
    pixels.allocate(w, h, OF_PIXELS_RGB);
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            // Motif damier avec dégradé
            int checker = ((x / 64) + (y / 64)) % 2;
            float gradient = (float)y / h;
            
            unsigned char r = checker ? 200 * gradient : 50;
            unsigned char g = checker ? 100 * gradient : 150;
            unsigned char b = checker ? 50 : 200 * gradient;
            
            pixels.setColor(x, y, ofColor(r, g, b));
        }
    }
    
    diffuseTexture.setFromPixels(pixels);
}

//--------------------------------------------------------------
void ofApp::setupLights() {
    // Lumière ponctuelle (Point Light)
    pointLight.setPointLight();
    pointLight.setPosition(200, 200, 200);
    pointLight.setDiffuseColor(ofColor(255, 200, 150));
    pointLight.setSpecularColor(ofColor(255, 255, 255));
    pointLight.setAttenuation(0.5, 0.001, 0.0001);
    
    // Lumière directionnelle
    directionalLight.setDirectional();
    directionalLight.setOrientation(ofVec3f(-45, -45, 0));
    directionalLight.setDiffuseColor(ofColor(100, 150, 200));
    directionalLight.setSpecularColor(ofColor(150, 150, 150));
}

//--------------------------------------------------------------
void ofApp::setupMaterials() {
    // Configuration du matériau (modèle de Phong)
    material.setShininess(specularPower);
    material.setSpecularColor(ofColor(255, 255, 255));
    material.setDiffuseColor(ofColor(200, 200, 200));
    material.setAmbientColor(ofColor(50, 50, 50));
}

//--------------------------------------------------------------
void ofApp::setupShader() {
    // Shader simple pour normal mapping
    string vertexShader = R"(
        #version 120
        
        varying vec3 v_normal;
        varying vec3 v_position;
        varying vec2 v_texcoord;
        varying vec3 v_lightDir;
        varying vec3 v_viewDir;
        
        uniform vec3 u_lightPos;
        
        void main() {
            v_position = vec3(gl_ModelViewMatrix * gl_Vertex);
            v_normal = normalize(gl_NormalMatrix * gl_Normal);
            v_texcoord = gl_MultiTexCoord0.xy;
            
            v_lightDir = normalize(u_lightPos - v_position);
            v_viewDir = normalize(-v_position);
            
            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
        }
    )";
    
    string fragmentShader = R"(
        #version 120
        
        varying vec3 v_normal;
        varying vec3 v_position;
        varying vec2 v_texcoord;
        varying vec3 v_lightDir;
        varying vec3 v_viewDir;
        
        uniform sampler2D u_diffuseTex;
        uniform sampler2D u_normalTex;
        uniform bool u_useTexture;
        uniform bool u_useNormalMap;
        uniform float u_ambientStrength;
        uniform float u_specularPower;
        uniform vec3 u_lightColor;
        
        void main() {
            vec3 normal = normalize(v_normal);
            
            // Normal mapping
            if (u_useNormalMap) {
                vec3 normalMap = texture2D(u_normalTex, v_texcoord).rgb * 2.0 - 1.0;
                normal = normalize(normalMap);
            }
            
            // Couleur de base
            vec3 baseColor = vec3(0.8, 0.8, 0.8);
            if (u_useTexture) {
                baseColor = texture2D(u_diffuseTex, v_texcoord).rgb;
            }
            
            // Composante ambiante
            vec3 ambient = u_ambientStrength * baseColor;
            
            // Composante diffuse (Lambert)
            float diff = max(dot(normal, v_lightDir), 0.0);
            vec3 diffuse = diff * u_lightColor * baseColor;
            
            // Composante spéculaire (Phong)
            vec3 reflectDir = reflect(-v_lightDir, normal);
            float spec = pow(max(dot(v_viewDir, reflectDir), 0.0), u_specularPower);
            vec3 specular = spec * u_lightColor;
            
            // Résultat final (modèle de Phong)
            vec3 result = ambient + diffuse + specular;
            
            gl_FragColor = vec4(result, 1.0);
        }
    )";
    
    normalMapShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
    normalMapShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
    normalMapShader.linkProgram();
}

//--------------------------------------------------------------
void ofApp::update() {
    rotation += 0.5;
    
    // Animation de la lumière
    float time = ofGetElapsedTimef();
    pointLight.setPosition(
        cos(time) * 300,
        sin(time * 0.7) * 200 + 100,
        sin(time) * 300
    );
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(30);
    
    cam.begin();
    
    // Activation des lumières
    ofEnableLighting();
    pointLight.enable();
    directionalLight.enable();
    
    drawScene();
    
    // Désactivation des lumières
    pointLight.disable();
    directionalLight.disable();
    ofDisableLighting();
    
    // Visualisation de la position de la lumière
    ofSetColor(255, 255, 0);
    ofDrawSphere(pointLight.getPosition(), 10);
    
    cam.end();
    
    // Interface utilisateur
    ofSetColor(255);
    ofDrawBitmapString("Contrôles:", 20, 20);
    ofDrawBitmapString("T: Toggle Texture (" + string(useTexture ? "ON" : "OFF") + ")", 20, 40);
    ofDrawBitmapString("N: Toggle Normal Map (" + string(useNormalMap ? "ON" : "OFF") + ")", 20, 60);
    ofDrawBitmapString("A/Z: Ambient (" + ofToString(ambientStrength, 2) + ")", 20, 80);
    ofDrawBitmapString("S/X: Specular Power (" + ofToString(specularPower, 1) + ")", 20, 100);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 0), 20, 120);
    
    ofDrawBitmapString("Module 6: Texture mapping sur les objets", 20, 160);
    ofDrawBitmapString("Module 7: Modèle d'illumination de Phong", 20, 180);
    ofDrawBitmapString("  - Composante ambiante, diffuse et spéculaire", 20, 200);
    ofDrawBitmapString("  - Lumières multiples (ponctuelle + directionnelle)", 20, 220);
}

//--------------------------------------------------------------
void ofApp::drawScene() {
    ofPushMatrix();
    
    // Sphère avec texture
    ofPushMatrix();
    ofTranslate(-150, 0, 0);
    ofRotateDeg(rotation, 0, 1, 0);
    
    if (useTexture) {
        normalMapShader.begin();
        normalMapShader.setUniform3f("u_lightPos", pointLight.getPosition());
        normalMapShader.setUniform1f("u_ambientStrength", ambientStrength);
        normalMapShader.setUniform1f("u_specularPower", specularPower);
        normalMapShader.setUniform3f("u_lightColor", 1.0, 1.0, 1.0);
        normalMapShader.setUniform1i("u_useTexture", useTexture);
        normalMapShader.setUniform1i("u_useNormalMap", useNormalMap);
        normalMapShader.setUniformTexture("u_diffuseTex", diffuseTexture, 0);
        
        sphere.draw();
        normalMapShader.end();
    } else {
        material.begin();
        sphere.draw();
        material.end();
    }
    ofPopMatrix();
    
    // Boîte
    ofPushMatrix();
    ofTranslate(150, 0, 0);
    ofRotateDeg(rotation * 0.7, 1, 1, 0);
    material.begin();
    box.draw();
    material.end();
    ofPopMatrix();
    
    // Cône
    ofPushMatrix();
    ofTranslate(0, -150, 0);
    ofRotateDeg(-rotation * 0.5, 0, 1, 1);
    material.begin();
    cone.draw();
    material.end();
    ofPopMatrix();
    
    // Plan au sol avec texture
    ofPushMatrix();
    ofTranslate(0, 200, 0);
    ofRotateDeg(-90, 1, 0, 0);
    
    if (useTexture) {
        diffuseTexture.bind();
    }
    material.begin();
    ofDrawPlane(0, 0, 600, 600);
    material.end();
    if (useTexture) {
        diffuseTexture.unbind();
    }
    ofPopMatrix();
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch(key) {
        case 't':
        case 'T':
            useTexture = !useTexture;
            break;
        case 'n':
        case 'N':
            useNormalMap = !useNormalMap;
            break;
        case 'a':
            ambientStrength = std::min(1.0f, ambientStrength + 0.05f);
            break;
        case 'z':
            ambientStrength = std::max(0.0f, ambientStrength - 0.05f);
            break;
        case 's':
            specularPower = std::min(128.0f, specularPower + 4.0f);
            break;
        case 'x':
            specularPower = std::max(1.0f, specularPower - 4.0f);
            break;
    }
}