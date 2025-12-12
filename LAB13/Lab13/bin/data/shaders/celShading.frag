#version 120

// Fragment Shader pour Cel Shading

// Variables d'entrée depuis le vertex shader
varying vec3 fragNormal;
varying vec3 fragPosition;
varying vec2 fragTexCoord;

// Uniforms (constantes pour tous les pixels)
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 objectColor;
uniform float celLevels;

void main() {
    // Normaliser la normale
    vec3 norm = normalize(fragNormal);
    
    // Direction de la lumière
    vec3 lightDir = normalize(lightPosition - fragPosition);
    
    // Calcul du dot product (cosinus de l'angle entre normal et lumière)
    float diff = max(dot(norm, lightDir), 0.0);
    
    // Discrétiser la valeur de luminosité (quantification)
    // Cela crée l'effet cartoon en divisant la luminosité en bandes
    float celShade = floor(diff * celLevels) / celLevels;
    
    // Couleur de base
    vec3 baseColor = objectColor;
    
    // Appliquer l'effet cel shading
    vec3 diffuseColor = baseColor * celShade;
    
    // Ajouter une couleur ambiante pour que les zones en ombre ne soient pas complètement noires
    vec3 ambientColor = baseColor * 0.3;
    
    // Combiner lumière diffuse et ambiante
    vec3 finalColor = mix(ambientColor, diffuseColor, celShade);
    
    gl_FragColor = vec4(finalColor, 1.0);
}
