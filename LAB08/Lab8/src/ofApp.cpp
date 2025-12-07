#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Load default image from data folder
    originalImage.load("cat.png");
    filteredImage = originalImage;
    currentFilter = 0;
    brightness = 0.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50);
    
    // Draw original image on the left
    originalImage.draw(20, 20);
    
    // Draw filtered image on the right
    filteredImage.draw(originalImage.getWidth() + 40, 20);
    
    // Draw instructions
    ofSetColor(255);
    int y = 40;
    ofDrawBitmapString("Controls:", 20, originalImage.getHeight() + y);
    ofDrawBitmapString("1: Grayscale", 20, originalImage.getHeight() + y + 20);
    ofDrawBitmapString("2: Blur", 20, originalImage.getHeight() + y + 40);
    ofDrawBitmapString("3: Edge Detection", 20, originalImage.getHeight() + y + 60);
    ofDrawBitmapString("4: Brightness (Up/Down arrows)", 20, originalImage.getHeight() + y + 80);
    ofDrawBitmapString("5: Color Inversion", 20, originalImage.getHeight() + y + 100);
    ofDrawBitmapString("R: Reset", 20, originalImage.getHeight() + y + 120);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case '1':
            applyGrayscale();
            break;
        case '2':
            applyBlur();
            break;
        case '3':
            applyEdgeDetection();
            break;
        case '4':
            applyBrightnessAdjustment();
            break;
        case '5':
            applyColorInversion();
            break;
        case 'r':
        case 'R':
            filteredImage = originalImage;
            brightness = 0.0f;
            break;
        case OF_KEY_UP:
            brightness = std::min(brightness + 0.1f, 1.0f);
            if(currentFilter == 4) applyBrightnessAdjustment();
            break;
        case OF_KEY_DOWN:
            brightness = std::max(brightness - 0.1f, -1.0f);
            if(currentFilter == 4) applyBrightnessAdjustment();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::applyGrayscale() {
    currentFilter = 1;
    filteredImage = originalImage;
    ofPixels& pixels = filteredImage.getPixels();
    
    for(size_t i = 0; i < pixels.size(); i += pixels.getNumChannels()) {
        float r = pixels[i];
        float g = pixels[i + 1];
        float b = pixels[i + 2];
        
        // Standard grayscale conversion weights
        float gray = 0.299f * r + 0.587f * g + 0.114f * b;
        
        pixels[i] = gray;
        pixels[i + 1] = gray;
        pixels[i + 2] = gray;
    }
    
    filteredImage.update();
}

//--------------------------------------------------------------
void ofApp::applyBlur() {
    currentFilter = 2;
    // 9x9 Gaussian blur kernel for much stronger effect
    vector<float> kernel = {
        1,  2,  3,   4,   5,   4,   3,  2, 1,
        2,  4,  6,   8,  10,   8,   6,  4, 2,
        3,  6,  9,  12,  15,  12,   9,  6, 3,
        4,  8, 12,  16,  20,  16,  12,  8, 4,
        5, 10, 15,  20,  25,  20,  15, 10, 5,
        4,  8, 12,  16,  20,  16,  12,  8, 4,
        3,  6,  9,  12,  15,  12,   9,  6, 3,
        2,  4,  6,   8,  10,   8,   6,  4, 2,
        1,  2,  3,   4,   5,   4,   3,  2, 1
    };
    
    // Normalize the kernel (divide by sum of all values)
    float sum = 0;
    for(float f : kernel) sum += f;
    for(float& f : kernel) f /= sum;
    
    applyConvolution(kernel, 9);
}

//--------------------------------------------------------------
void ofApp::applyEdgeDetection() {
    currentFilter = 3;
    // Sobel operator (vertical edges)
    vector<float> kernel = {
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    };
    applyConvolution(kernel, 3);
}

//--------------------------------------------------------------
void ofApp::applyBrightnessAdjustment() {
    currentFilter = 4;
    filteredImage = originalImage;
    ofPixels& pixels = filteredImage.getPixels();
    
    for(size_t i = 0; i < pixels.size(); i++) {
        float pixel = pixels[i];
        if(brightness > 0) {
            pixel = pixel + (255 - pixel) * brightness;
        } else {
            pixel = pixel + pixel * brightness;
        }
        pixels[i] = ofClamp(pixel, 0, 255);
    }
    
    filteredImage.update();
}

//--------------------------------------------------------------
void ofApp::applyColorInversion() {
    currentFilter = 5;
    filteredImage = originalImage;
    ofPixels& pixels = filteredImage.getPixels();
    int channels = pixels.getNumChannels();
    
    for(size_t i = 0; i < pixels.size(); i += channels) {
        // Invert RGB channels but preserve alpha
        pixels[i] = 255 - pixels[i];         // R
        pixels[i + 1] = 255 - pixels[i + 1]; // G
        pixels[i + 2] = 255 - pixels[i + 2]; // B
        // Skip alpha channel if it exists (i + 3)
    }
    
    filteredImage.update();
}

//--------------------------------------------------------------
void ofApp::applyConvolution(const vector<float>& kernel, int kernelSize) {
    filteredImage = originalImage;
    ofPixels originalPixels = originalImage.getPixels();
    ofPixels& pixels = filteredImage.getPixels();
    
    int w = originalImage.getWidth();
    int h = originalImage.getHeight();
    int channels = originalImage.getPixels().getNumChannels();
    
    // Create a temporary copy for edge handling
    ofPixels tempPixels = originalPixels;
    
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            // Only apply convolution to RGB channels, preserve alpha if it exists
            for(int c = 0; c < std::min(3, channels); c++) {
                float sum = 0;
                float kernelSum = 0;  // For edge normalization
                
                for(int ky = 0; ky < kernelSize; ky++) {
                    for(int kx = 0; kx < kernelSize; kx++) {
                        int pixel_x = x + kx - kernelSize/2;
                        int pixel_y = y + ky - kernelSize/2;
                        
                        // Edge handling: mirror pixels at boundaries
                        if(pixel_x < 0) pixel_x = -pixel_x;
                        if(pixel_y < 0) pixel_y = -pixel_y;
                        if(pixel_x >= w) pixel_x = 2*w - pixel_x - 2;
                        if(pixel_y >= h) pixel_y = 2*h - pixel_y - 2;
                        
                        float k = kernel[ky * kernelSize + kx];
                        float pixel_value = originalPixels[(pixel_y * w + pixel_x) * channels + c];
                        sum += k * pixel_value;
                        kernelSum += k;
                    }
                }
                
                // Normalize and clamp the result
                if(kernelSum != 0) sum /= kernelSum;
                pixels[(y * w + x) * channels + c] = ofClamp(sum, 0, 255);
            }
            
            // Preserve alpha channel if it exists
            if(channels == 4) {
                pixels[(y * w + x) * channels + 3] = originalPixels[(y * w + x) * channels + 3];
            }
        }
    }
    
    filteredImage.update();
}

void ofApp::exit(){
}

void ofApp::keyReleased(int key){
}

void ofApp::mouseMoved(int x, int y){
}

void ofApp::mouseDragged(int x, int y, int button){
}

void ofApp::mousePressed(int x, int y, int button){
}

void ofApp::mouseReleased(int x, int y, int button){
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
}

void ofApp::mouseEntered(int x, int y){
}

void ofApp::mouseExited(int x, int y){
}

void ofApp::windowResized(int w, int h){
}

void ofApp::gotMessage(ofMessage msg){
}

void ofApp::dragEvent(ofDragInfo dragInfo){
}
