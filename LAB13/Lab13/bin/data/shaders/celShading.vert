#version 120

// Vertex Shader pour Cel Shading

// Variables de sortie vers le fragment shader
varying vec3 fragNormal;
varying vec3 fragPosition;
varying vec2 fragTexCoord;

void main() {
    // Transformer la position en espace écran
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    // Transformer la normale en espace caméra
    fragNormal = normalize(gl_NormalMatrix * gl_Normal);
    
    // Position en espace caméra
    fragPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
    
    // Passer les coordonnées de texture
    fragTexCoord = vec2(gl_MultiTexCoord0);
}
