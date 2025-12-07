#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofEnableDepthTest();
	ofEnableLighting();
	
	// Initialiser les variables
	rotation = 0.0f;
	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;
	bumpIntensity = 0.5f;
	lightPosition = glm::vec3(5.0f, 3.0f, 5.0f);
	meshResolution = 100;
	useColorTexture = false;
	
	// Configurer la caméra de base
	ofSetupScreen();
	
	// Générer la texture de heightmap
	generateHeightMapTexture();
	
	// Essayer de charger une texture couleur
	loadColorTexture();
	
	// Générer le mesh avec relief
	generateReliefMesh();
}

//--------------------------------------------------------------
void ofApp::loadColorTexture(){
	// Chercher et charger un fichier PNG dans le dossier bin/data/
	if(colorTexture.load("texture.png")){
		useColorTexture = true;
		ofLogNotice() << "Texture chargée: texture.png";
	} else if(colorTexture.load("data/texture.png")){
		useColorTexture = true;
		ofLogNotice() << "Texture chargée: data/texture.png";
	} else {
		useColorTexture = false;
		ofLogWarning() << "Aucune texture trouvée. Placez texture.png dans bin/ ou bin/data/";
	}
}

//--------------------------------------------------------------
void ofApp::generateHeightMapTexture(){
	// Créer une heightmap avec du bruit Perlin
	int width = 256;
	int height = 256;
	
	ofPixels pixels;
	pixels.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			// Bruit Perlin multicouche pour un effet naturel
			float value = ofNoise(x * 0.005f, y * 0.005f) * 0.5f +
						  ofNoise(x * 0.01f, y * 0.01f) * 0.3f +
						  ofNoise(x * 0.02f, y * 0.02f) * 0.2f;
			
			value = ofClamp(value, 0.0f, 1.0f);
			unsigned char val = (unsigned char)(value * 255);
			pixels[y * width + x] = val;
		}
	}
	
	heightMapTexture.setFromPixels(pixels);
}

//--------------------------------------------------------------
void ofApp::generateReliefMesh(){
	reliefMesh.clear();
	
	float meshSize = 10.0f;
	
	// Créer les vertices et indices du mesh
	for(int y = 0; y <= meshResolution; y++){
		for(int x = 0; x <= meshResolution; x++){
			float px = (x / (float)meshResolution - 0.5f) * meshSize;
			float pz = (y / (float)meshResolution - 0.5f) * meshSize;
			
			// Normaliser les coordonnées pour accéder à la heightmap
			float tx = x / (float)meshResolution;
			float ty = y / (float)meshResolution;
			
			// Lire la hauteur depuis la heightmap en utilisant getColor
			ofColor heightColor = heightMapTexture.getColor(
				(int)(tx * (heightMapTexture.getWidth() - 1)),
				(int)(ty * (heightMapTexture.getHeight() - 1))
			);
			float heightVal = heightColor.getBrightness() / 255.0f;
			
			float py = heightVal * bumpIntensity * 2.0f;
			
			// Ajouter le vertex
			reliefMesh.addVertex(glm::vec3(px, py, pz));
			reliefMesh.addTexCoord(glm::vec2(tx, ty));
			
			// Couleur basée sur la hauteur avec un gradient de couleurs
			unsigned char colorVal = (unsigned char)(heightVal * 200 + 50);
			
			if(useColorTexture){
				// Charger la couleur depuis la texture
				ofColor texColor = colorTexture.getColor(
					(int)(tx * (colorTexture.getWidth() - 1)),
					(int)(ty * (colorTexture.getHeight() - 1))
				);
				reliefMesh.addColor(texColor);
			} else {
				// Gradient de couleurs du bleu (bas) au rouge (haut)
				float r = heightVal * 255;  // Plus rouge en hauteur
				float g = heightVal * 150;  // Un peu de vert
				float b = (1.0f - heightVal) * 200;  // Bleu inverse
				reliefMesh.addColor(ofColor(r, g, b, 255));
			}
		}
	}
	
	// Créer les indices (triangles)
	for(int y = 0; y < meshResolution; y++){
		for(int x = 0; x < meshResolution; x++){
			int a = y * (meshResolution + 1) + x;
			int b = a + 1;
			int c = a + (meshResolution + 1);
			int d = c + 1;
			
			// Premier triangle
			reliefMesh.addIndex(a);
			reliefMesh.addIndex(c);
			reliefMesh.addIndex(b);
			
			// Deuxième triangle
			reliefMesh.addIndex(b);
			reliefMesh.addIndex(c);
			reliefMesh.addIndex(d);
		}
	}
	
	// Calculer les normales
	reliefMesh.disableNormals();
	reliefMesh.enableNormals();
}

//--------------------------------------------------------------
void ofApp::update(){
	// Pas de rotation automatique
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofClear(40, 40, 40);
	
	// Configurer la caméra avec la perspective
	float fov = 45.0f;
	float aspect = (float)ofGetWidth() / (float)ofGetHeight();
	float near = 0.1f;
	float far = 100.0f;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float f = 1.0f / tan(ofDegToRad(fov / 2.0f));
	float A = (far + near) / (near - far);
	float B = (2.0f * far * near) / (near - far);
	glFrustum(-1.0f/f/aspect, 1.0f/f/aspect, -1.0f/f, 1.0f/f, near, far);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, -1, -8);
	
	ofEnableLighting();
	ofEnableDepthTest();
	
	// Configurer les lumières
	ofLight light;
	light.setPosition(lightPosition.x, lightPosition.y, lightPosition.z);
	light.setAmbientColor(ofColor(80, 80, 80));
	light.setDiffuseColor(ofColor(200, 200, 200));
	light.setSpecularColor(ofColor(255, 255, 255));
	light.enable();
	
	// Matériau
	ofMaterial material;
	material.setDiffuseColor(ofColor(150, 150, 150));
	material.setSpecularColor(ofColor(255, 255, 255));
	material.setShininess(100);
	material.begin();
	
	// Rotation et rendu
	ofPushMatrix();
	ofRotateDeg(rotationX, 1, 0, 0);
	ofRotateDeg(rotationY, 0, 1, 0);
	ofRotateDeg(rotationZ, 0, 0, 1);
	
	// Vérifier que le mesh n'est pas vide
	if(reliefMesh.getNumVertices() > 0){
		reliefMesh.draw();
	}
	
	ofPopMatrix();
	
	material.end();
	light.disable();
	
	// Reset pour l'interface
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, ofGetWidth(), ofGetHeight(), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Affichage de l'interface
	ofDisableLighting();
	ofDisableDepthTest();
	
	ofSetColor(255);
	ofDrawBitmapString("Relief Effect - Heightmap Displacement", 20, 20);
	ofDrawBitmapString("Relief Intensity: " + ofToString(bumpIntensity, 2) + " (Use +/- keys)", 20, 40);
	ofDrawBitmapString("Rotation - Arrow Keys: X=" + ofToString(rotationX, 1) + " Y=" + ofToString(rotationY, 1) + " Z=" + ofToString(rotationZ, 1), 20, 60);
	ofDrawBitmapString("Light Position: (" + ofToString(lightPosition.x, 1) + ", " + 
					   ofToString(lightPosition.y, 1) + ", " + ofToString(lightPosition.z, 1) + ")", 20, 80);
	ofDrawBitmapString("Vertices: " + ofToString(reliefMesh.getNumVertices()) + 
					   " | Indices: " + ofToString(reliefMesh.getNumIndices()), 20, 100);
	
	// Afficher l'état de la texture
	if(useColorTexture){
		ofSetColor(0, 255, 0);
		ofDrawBitmapString("Texture: LOADED (" + ofToString(colorTexture.getWidth()) + "x" + ofToString(colorTexture.getHeight()) + ") | Press 't' to toggle", 20, 120);
	} else {
		ofSetColor(255, 100, 100);
		ofDrawBitmapString("Texture: NOT FOUND | Place texture.png in bin/ or bin/data/ | Press 't' to toggle", 20, 120);
	}
	
	ofSetColor(255);
	ofDrawBitmapString("Controls: +/- (intensity) | Arrow Keys (rotate) | r (reset) | t (toggle texture) | Mouse (light)", 20, 140);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == '+' || key == '='){
		bumpIntensity = glm::min(bumpIntensity + 0.1f, 2.0f);
		generateReliefMesh();
	}
	else if(key == '-' || key == '_'){
		bumpIntensity = glm::max(bumpIntensity - 0.1f, 0.0f);
		generateReliefMesh();
	}
	else if(key == 'r' || key == 'R'){
		bumpIntensity = 0.5f;
		rotationX = 0.0f;
		rotationY = 0.0f;
		rotationZ = 0.0f;
		lightPosition = glm::vec3(5.0f, 3.0f, 5.0f);
		generateReliefMesh();
	}
	// Flèches pour la rotation
	else if(key == OF_KEY_UP){
		rotationX += 5.0f;
	}
	else if(key == OF_KEY_DOWN){
		rotationX -= 5.0f;
	}
	else if(key == OF_KEY_LEFT){
		rotationY -= 5.0f;
	}
	else if(key == OF_KEY_RIGHT){
		rotationY += 5.0f;
	}
	else if(key == 't' || key == 'T'){
		// Basculer entre texture et gradient
		if(useColorTexture){
			useColorTexture = false;
		} else {
			loadColorTexture();
		}
		generateReliefMesh();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	// Contrôler la position de la lumière avec la souris
	lightPosition.x = (x - ofGetWidth() / 2.0f) * 0.02f;
	lightPosition.z = (y - ofGetHeight() / 2.0f) * 0.02f;
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
