# Guide de démarrage rapide - Cel Shading

## 📝 Résumé du projet

Voici un programme complet de **cel shading** (rendu cartoon) développé avec **openFrameworks** et **GLSL**.

### Fichiers créés:

```
Lab13/
├── src/
│   ├── ofApp.h              ← Header avec les variables
│   └── ofApp.cpp            ← Implémentation principale
│
├── bin/data/shaders/
│   ├── celShading.vert      ← Vertex shader
│   └── celShading.frag      ← Fragment shader (CEL SHADING!)
│
└── Documentation:
    ├── CEL_SHADING_README.md       ← Théorie complète
    ├── INSTRUCTIONS.md              ← Comment compiler
    ├── EXPLICATION_TECHNIQUE.md     ← Visuels + formules
    └── AMELIORATIONS.md             ← Extensions avancées
```

## 🚀 Pour commencer (3 étapes)

### 1. Compiler
```bash
cd Lab13
make
```

### 2. Exécuter
```bash
./bin/Lab13
```

### 3. Contrôler
- **Touches de touche:**
  - **1** : Changer d'objet (sphère → cube → icosphere)
  - **2, 3, 4** : Changer de couleur
  - **W/A/S/D** : Bouger lumière en XY
  - **Q/E** : Avant/Arrière
  - **Flèches UP/DOWN** : Plus/moins de niveaux cel shading
  - **ESPACE** : Réinitialiser

## 🎨 Qu'est-ce que c'est?

Le **cel shading** est une technique qui fait ressembler les objets 3D à des dessins animés. Au lieu d'avoir une transition lisse entre l'ombre et la lumière, on a des **bandes discrètes de couleur**.

### Visuel:

```
Normal (lisse):      Cel Shading (cartoon):
    ███                  ███
   █████           →     ███
  ███████               ███
Transition              Bandes
continue               discrètes
```

## 💡 Le code clé (Fragment Shader)

La magie se passe dans ce shader qui fait la **quantification**:

```glsl
// Calcul normal de la luminosité
float diff = max(dot(norm, lightDir), 0.0);

// QUANTIFICATION: Transformer en bandes discrètes!
float celShade = floor(diff * celLevels) / celLevels;

// Appliquer à la couleur
vec3 finalColor = objectColor * celShade;
```

Exemple avec 3 niveaux:
- Luminosité 0.0-0.33 → 0.0 (noir)
- Luminosité 0.33-0.66 → 0.33 (gris)
- Luminosité 0.66-1.0 → 0.66 (clair)

## 🎮 Paramètres interactifs

Dans le programme, vous pouvez modifier:

| Paramètre | Contrôle | Effet |
|-----------|----------|--------|
| **celLevels** | Flèches UP/DOWN | Nombre de bandes de couleur (1-10) |
| **Couleur** | Touches 2/3/4 | Rouge, Vert, Bleu |
| **Lumière** | WASD + QE | Position de la source lumineuse |
| **Objet** | Touche 1 | Sphère, Cube, Icosphere |

## 📖 Apprendre plus

### Fichiers de documentation inclus:

1. **CEL_SHADING_README.md**
   - Explication complète de la technique
   - Applications réelles (jeux vidéo, films)
   - Extension possibles

2. **EXPLICATION_TECHNIQUE.md**
   - Formules mathématiques
   - Diagrammes visuels
   - Étapes du pipeline GPU
   - Code détaillé du shader

3. **AMELIORATIONS.md**
   - Ajouter des contours
   - Reflets (specular highlights)
   - Textures
   - Animations
   - Lumières multiples

## 🔧 Structure du code C++

### `ofApp.h` - Déclarations

```cpp
class ofApp {
private:
    ofShader celShader;              // Le shader
    ofSpherePrimitive sphere;        // Les objets 3D
    glm::vec3 lightPosition;         // Position lumière
    float celLevels;                 // Nombre de bandes
};
```

### `ofApp.cpp` - Implémentation

```cpp
setup()   → Charger les shaders et configurer
update()  → Rotation de l'objet
draw()    → Appliquer le shader et dessiner
keyPressed() → Gérer les contrôles
```

## 🎯 Objectifs du projet

✅ **Identifié une technique** : Cel Shading  
✅ **Recherché l'information** : Formules, concepts, applications  
✅ **Développé un programme** : Code C++ + shaders GLSL  
✅ **Mis en application** : Scène 3D interactive avec ce rendu  

## 🌟 Points clés

- **Shader principal**: Quantification de la luminosité
- **Interaction**: 10+ contrôles pour explorer l'effet
- **Documentation**: Complète et progressive
- **Extensibilité**: Facile d'ajouter des améliorations

## ❓ FAQ

**Q: Pourquoi ça regarde comme un dessin?**  
A: Parce que la quantification crée des bandes au lieu de dégradés lisses, comme les techniques de dessin anime.

**Q: Qu'est-ce que celLevels?**  
A: Le nombre de niveaux de luminosité discrets. Plus le nombre est élevé, plus c'est détaillé.

**Q: Les shaders se compilent quand?**  
A: À la première exécution et à chaque rechargement du programme (pas besoin de recompiler le C++).

**Q: Puis-je ajouter d'autres objets?**  
A: Oui! Créez simplement d'autres primitives dans `setup()` et changez le code dans `draw()`.

**Q: Comment ajouter un contour noir?**  
A: Consultez **AMELIORATIONS.md** - Section 1 pour l'edge detection.

## 📚 Ressources supplémentaires

### Concepts fondamentaux:
- Normal mapping
- Dot product (produit scalaire)
- Shaders GLSL
- Éclairage Lambertien

### Prochaines étapes:
1. Ajouter des contours
2. Combiner avec des textures
3. Implémenter plusieurs lumières
4. Créer une scène complète

## 📞 Pour déboguer

Si quelque chose ne fonctionne pas:

1. Vérifiez que les shaders sont dans `bin/data/shaders/`
2. Vérifiez les erreurs de compilation à l'écran
3. Augmentez la résolution (setResolution) pour mieux voir
4. Essayez de réduire celLevels pour voir des changements nets

Bon amusement! 🎨✨
