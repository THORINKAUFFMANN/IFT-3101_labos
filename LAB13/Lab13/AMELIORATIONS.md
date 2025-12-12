# Améliorations et extensions du Cel Shading

## Extensions possibles

### 1. Ajouter des contours (Edge Detection)

**Concept:** Détecter les silhouettes et les tracer en noir

**Implémentation simple:**
```glsl
// Dans le fragment shader
float outlineWidth = 0.02;
vec3 edge = abs(cross(norm, normalize(viewDir)));
if (edge.x < outlineWidth || edge.y < outlineWidth || edge.z < outlineWidth) {
    fragColor = vec4(0.0, 0.0, 0.0, 1.0); // Noir
}
```

**Résultat visuel:**
```
Sans contour:          Avec contour:
    ███                    ▓▓▓
   █████          →       ▓███▓
  ███████                ▓███████▓
```

### 2. Specular Highlights (Reflets)

**Concept:** Ajouter des reflets brillants discrets

**Code:**
```glsl
// Après calcul de diffuse
vec3 viewDir = normalize(viewPosition - fragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

// Quantifier le specular aussi
float celSpec = floor(spec * 3.0) / 3.0;
vec3 specColor = vec3(1.0) * celSpec;

finalColor += specColor * 0.5;
```

### 3. Texture Mapping avec Cel Shading

**Concept:** Appliquer une texture tout en gardant l'effet cartoon

**Vertex Shader:**
```glsl
out vec2 fragTexCoord;

void main() {
    fragTexCoord = texcoord;
    // ... reste du code ...
}
```

**Fragment Shader:**
```glsl
uniform sampler2D textureSampler;

void main() {
    // Charger la couleur de la texture
    vec4 texColor = texture(textureSampler, fragTexCoord);
    
    // Appliquer le cel shading
    float diff = max(dot(norm, lightDir), 0.0);
    float celShade = floor(diff * celLevels) / celLevels;
    
    // Combiner texture + cel shading
    vec3 finalColor = texColor.rgb * celShade;
    fragColor = vec4(finalColor, texColor.a);
}
```

### 4. Multi-objets avec paramètres indépendants

**Extension du code C++:**
```cpp
class CelObject {
public:
    ofBasePrimitive* geometry;
    glm::vec3 color;
    float celLevels;
    float rotation;
    
    void draw(ofShader& shader) {
        ofPushMatrix();
        ofRotateDeg(rotation, 0, 1, 0);
        
        shader.setUniform3f("objectColor", color.x, color.y, color.z);
        shader.setUniform1f("celLevels", celLevels);
        
        geometry->draw();
        ofPopMatrix();
    }
};

// Dans ofApp
vector<CelObject> objects;
```

### 5. Animation des paramètres

**Concept:** Animer la lumière, les couleurs, ou celLevels

**Code:**
```cpp
void ofApp::update() {
    // Lumière orbitale
    float time = ofGetElapsedTimef();
    lightPosition.x = sin(time) * 200;
    lightPosition.z = cos(time) * 200;
    
    // Couleur qui change
    objectColor.x = sin(time * 0.5f) * 0.5f + 0.5f;
    objectColor.y = sin(time * 0.7f) * 0.5f + 0.5f;
    objectColor.z = sin(time * 0.9f) * 0.5f + 0.5f;
    
    // CelLevels qui pulse
    celLevels = sin(time * 2.0f) * 3.0f + 4.0f;
}
```

### 6. Post-processing: Posterize Effect

**Concept:** Réduire le nombre de couleurs dans toute l'image

**Fragment Shader complet:**
```glsl
#version 150

in vec3 fragNormal;
in vec3 fragPosition;

uniform vec3 lightPosition;
uniform vec3 objectColor;
uniform float celLevels;
uniform float posterizeLevels; // Nouveau!

out vec4 fragColor;

void main() {
    // Cel shading normal
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    float celShade = floor(diff * celLevels) / celLevels;
    
    vec3 baseColor = objectColor;
    vec3 diffuseColor = baseColor * celShade;
    vec3 ambientColor = baseColor * 0.3;
    vec3 finalColor = mix(ambientColor, diffuseColor, celShade);
    
    // Post-processing: Posterize chaque canal
    finalColor.r = floor(finalColor.r * posterizeLevels) / posterizeLevels;
    finalColor.g = floor(finalColor.g * posterizeLevels) / posterizeLevels;
    finalColor.b = floor(finalColor.b * posterizeLevels) / posterizeLevels;
    
    fragColor = vec4(finalColor, 1.0);
}
```

### 7. Éclairage directional vs ponctuel

**Lumière directionnelle (comme le soleil):**
```glsl
// Au lieu d'une position ponctuelle
uniform vec3 lightDirection; // Direction, pas position
vec3 lightDir = normalize(-lightDirection); // Inverser pour avoir vers la lumière
```

**Lumière multiples:**
```glsl
float calculateCelLight(vec3 lightPos, vec3 lightColor) {
    vec3 lightDir = normalize(lightPos - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    float celShade = floor(diff * celLevels) / celLevels;
    return celShade;
}

void main() {
    float light1 = calculateCelLight(lightPos1, color1);
    float light2 = calculateCelLight(lightPos2, color2);
    float combined = light1 + light2;
    
    fragColor = vec4(objectColor * combined, 1.0);
}
```

### 8. Rim Lighting (Éclairage de bordure)

**Concept:** Illuminer les bords de l'objet

```glsl
void main() {
    vec3 viewDir = normalize(viewPosition - fragPosition);
    
    // Rim lighting effect
    float rim = 1.0 - dot(viewDir, norm);
    rim = smoothstep(0.0, 1.0, rim);
    
    // Appliquer cel shading
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    float celShade = floor(diff * celLevels) / celLevels;
    
    vec3 baseColor = objectColor;
    vec3 finalColor = baseColor * celShade + rim * 0.5;
    
    fragColor = vec4(finalColor, 1.0);
}
```

### 9. Performance: Utiliser des textures pour pré-calculer

**Concept:** Utiliser une "ramp texture" pour les niveaux

```glsl
uniform sampler1D rampTexture; // Texture 1D

void main() {
    float diff = max(dot(norm, lightDir), 0.0);
    
    // Au lieu de floor/division, utiliser la texture
    vec3 rampColor = texture(rampTexture, diff).rgb;
    
    vec3 finalColor = objectColor * rampColor;
    fragColor = vec4(finalColor, 1.0);
}
```

**Avantage:** Plus flexible et plus rapide

### 10. Styles de dessin avancés

**Hachage (Hatching):**
```glsl
// Ajouter des traits basés sur la luminosité
float hatch = sin(fragPosition.x * 10.0) * sin(fragPosition.y * 10.0);
if (celShade < 0.3 && hatch > 0.5) {
    finalColor = vec3(0.0); // Noir pour les ombres
}
```

**Pointillisme:**
```glsl
// Utiliser le noise pour créer des points
float noise = fract(sin(fragPosition.x * 12.9898 + fragPosition.y * 78.233) * 43758.5453);
if (celShade < 0.5 && noise > 0.7) {
    finalColor *= 0.8;
}
```

## Recommandations pour le cours

### Pour débuter:
1. Maîtrisez d'abord les bases du cel shading simple
2. Testez avec différents celLevels
3. Comprenez comment les shaders se chargent

### Pour progresser:
1. Ajoutez des contours simples
2. Implémentez le specular highlights
3. Testez avec plusieurs objets

### Pour progresser davantage:
1. Combinez avec des textures
2. Implémentez des lumières multiples
3. Créez une scène complexe

## Ressources pour apprendre

### Documentations:
- OpenFrameworks: https://openframeworks.cc/
- GLSL Sandbox: https://glslsandbox.com/
- Shader Toy: https://www.shadertoy.com/

### Tutoriels vidéo:
- "Cel Shading Explained" - LearnOpenGL
- "GLSL Basics" - The Cherno

### Livres:
- "Real-Time Rendering" - Akenine-Möller, Haines, Hoffman
- "OpenGL 4.0 Shading Language Cookbook"

## Défi: Créer votre propre shader!

Essayez de combiner:
1. Cel shading basique
2. Contours
3. Spécularité
4. Animation

**Exemple complet:**
```cpp
// Dans update()
float time = ofGetElapsedTimef();
lightPosition.y = sin(time) * 100 + 200;
celLevels = 3.0 + sin(time * 0.5) * 2.0;

// Dans draw()
// Appliquer et observer le résultat!
```

Bon codage! 🎨✨
