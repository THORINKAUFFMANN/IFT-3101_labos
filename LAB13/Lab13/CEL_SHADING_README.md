# Démonstration du Cel Shading

## Vue d'ensemble

Ce projet démontre la technique de rendu **Cel Shading** (rendu non-photoréaliste ou NPR - Non-Photorealistic Rendering), aussi appelée **Toon Shading**. C'est une technique de rendu qui donne aux objets 3D un apparence semblable à un dessin animé ou une bande dessinée.

## Qu'est-ce que le Cel Shading?

### Concept principal
Le cel shading est une technique qui **quantifie les niveaux de luminosité** au lieu d'utiliser un dégradé continu. Au lieu d'avoir une transition en douceur de l'ombre à la lumière, on a des bandes de couleur distinctes et bien définies.

### Différence avec le rendu classique

**Rendu classique (Gouraud/Phong):**
- Calcul lisse et continu de la luminosité
- Les objets paraissent réalistes mais lisses
- Dégradés graduels entre clair et foncé

**Cel Shading:**
- Luminosité quantifiée en bandes discrètes
- Apparence de dessin animé ou cartoon
- Bandes de couleur bien distinctes, comme dans une bande dessinée

## Implémentation

### Architecture du projet

```
src/
├── main.cpp          # Entrée du programme et configuration de la fenêtre
├── ofApp.h           # Déclaration de la classe principale
└── ofApp.cpp         # Implémentation du moteur de rendu

bin/data/shaders/
├── celShading.vert   # Vertex shader
└── celShading.frag   # Fragment shader
```

### Les Shaders

#### Vertex Shader (`celShading.vert`)
Le vertex shader:
1. Transforme les positions des vertices en espace écran
2. Transforme les normales en espace caméra
3. Passe ces informations au fragment shader

#### Fragment Shader (`celShading.frag`)
C'est ici que la magie du cel shading se produit:

1. **Calcul de l'éclairage Lambertien:**
   ```glsl
   float diff = max(dot(norm, lightDir), 0.0);
   ```
   Calcule la luminosité basée sur l'angle entre la normale et la lumière.

2. **Quantification (l'étape clé du cel shading):**
   ```glsl
   float celShade = floor(diff * celLevels) / celLevels;
   ```
   Divise la luminosité continue en bandes discrètes. Par exemple:
   - Avec `celLevels = 3`: on obtient 3 niveaux (noir, gris, blanc)
   - Avec `celLevels = 5`: on obtient 5 niveaux pour plus de détails

3. **Application de la couleur:**
   Combine la couleur de base avec le shading calculé.

4. **Lumière ambiante:**
   Ajoute une teinte ambiante pour que les zones en ombre ne soient pas entièrement noires.

## Mathématiques derrière le cel shading

### Formule de luminosité Lambertienne
$$L = \max(0, N \cdot L)$$

Où:
- $N$ = normale de la surface
- $L$ = direction vers la lumière
- Le résultat est entre 0 (complètement à l'ombre) et 1 (face à la lumière)

### Quantification (Ceil Shading)
$$Q = \lfloor D \times n \rfloor / n$$

Où:
- $D$ = valeur de luminosité continue (0 à 1)
- $n$ = nombre de niveaux de luminosité
- $\lfloor \rfloor$ = fonction plancher (floor)

Exemple avec $n = 3$:
- Luminosité 0.0-0.33 → 0 (noir)
- Luminosité 0.33-0.66 → 0.33 (gris moyen)
- Luminosité 0.66-1.0 → 0.66 (gris clair)

## Contrôles du programme

### Interactions disponibles

| Touche | Action |
|--------|--------|
| **1** | Changer d'objet (Sphère → Cube → Icosphere) |
| **2** | Couleur rouge |
| **3** | Couleur verte |
| **4** | Couleur bleue |
| **W/S** | Déplacer la lumière en Y (haut/bas) |
| **A/D** | Déplacer la lumière en X (gauche/droite) |
| **Q/E** | Déplacer la lumière en Z (avant/arrière) |
| **Flèche UP** | Augmenter le nombre de niveaux de cel shading |
| **Flèche DOWN** | Diminuer le nombre de niveaux |
| **ESPACE** | Réinitialiser tout |

### Observables

- Les objets tournent continuellement pour montrer l'effet du cel shading
- La lumière jaune montre la position actuelle de la source lumineuse
- Vous pouvez voir comment les niveaux de luminosité changent selon la position de la lumière
- Modifier `celLevels` change le nombre de bandes de couleur visibles

## Paramètres modifiables

Dans `setup()`, vous pouvez ajuster:

```cpp
celLevels = 3.0f;           // Nombre de niveaux (1-10)
objectColor = glm::vec3();  // Couleur RGB de l'objet
lightPosition = glm::vec3();// Position de la lumière
```

## Extensions possibles

1. **Outline (contours):** Ajouter des contours noirs autour des silhouettes
2. **Spécularité:** Ajouter des reflets brillants discrets
3. **Multi-objets:** Rendre plusieurs objets avec des paramètres différents
4. **Texture:** Appliquer des textures avec le cel shading
5. **Animation:** Animer les propriétés des shaders

## Références et ressources

### Concept historique
Le cel shading a été popularisé par des jeux vidéo comme:
- The Legend of Zelda: The Wind Waker (2002)
- Borderlands (2009)

### Applications pratiques
- Jeux vidéo indie et AAA
- Animation 3D stylisée
- Films d'animation
- Visualization scientifique

## Notes techniques

- Le programme utilise OpenGL via openFrameworks
- Les shaders sont en GLSL 1.50 (compatible avec la plupart des GPU modernes)
- La résolution des objets 3D affecte la qualité du rendu
- Le nombre de niveaux affecte fortement l'apparence cartoon
