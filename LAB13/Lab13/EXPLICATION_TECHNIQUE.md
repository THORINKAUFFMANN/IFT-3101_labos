# Cel Shading - Explication visuelle et théorique

## 1. Concept de base du Cel Shading

### Comparaison: Rendu lisse vs Cel Shading

```
RENDU LISSE (Gouraud/Phong)
┌─────────────────────────────────┐
│███░░░░░░░░░░░░░░░░░░░░░░░░░░░││
│██████░░░░░░░░░░░░░░░░░░░░░░│││
│███████████░░░░░░░░░░░░░░░███│
│████████████████░░░░░░░░████││
└─────────────────────────────────┘
Dégradé continu et lisse

CEL SHADING (Toon Shading)
┌─────────────────────────────────┐
│█████████│░░░░░░░░│▒▒▒▒▒▒▒▒│███│
│█████████│░░░░░░░░│▒▒▒▒▒▒▒▒│███│
│█████████│░░░░░░░░│▒▒▒▒▒▒▒▒│███│
│█████████│░░░░░░░░│▒▒▒▒▒▒▒▒│███│
└─────────────────────────────────┘
Bandes discrètes de couleur
```

## 2. Le processus mathématique

### Étape 1: Calcul de la luminosité Lambertienne

**Formule:**
```
diffuse = max(0, Normal · LightDirection)
```

**Visualisation:**

```
        Lumière
           ⬇
      ╭────•────╮
      │   /     │
      │  /      │
      │ / 90°   │  → diffuse = 0 (normal perpendiculaire)
      │/        │
      ├─────────┤

        Lumière
           ⬇
      ╭────•─────╮
      │  /       │
      │ /        │
      │/ 45°     │  → diffuse ≈ 0.7 (angle oblique)
      │/         │
      ├──────────┤

        Lumière
           │
      ╭────•─────╮
      │  │       │
      │  │       │
      │  │ 0°    │  → diffuse = 1.0 (face à la lumière)
      │  │       │
      ├──────────┤
```

**Résultat:** Valeur de luminosité entre 0.0 (noir) et 1.0 (blanc)

### Étape 2: Quantification (la clé du cel shading!)

**Processus:**

```
Valeur de luminosité continue:
0.0 ──────┬──────┬──────┬────── 1.0
          │      │      │
          │      │      └─ Très clair
          │      └────────── Clair
          └─────────────────── Foncé

Avec celLevels = 3:
          ╎      ╎      ╎
0.0 ──────┼──────┼──────┼────── 1.0
   ▓▓▓▓▓▓▓│░░░░░░│▒▒▒▒▒▒│
   (1/3)  (2/3)  (3/3)
```

**Formule:**

```
quantified = floor(luminosité × celLevels) / celLevels

Exemple avec celLevels = 3:
- luminosité = 0.15 → floor(0.15 × 3) / 3 = floor(0.45) / 3 = 0 / 3 = 0.0
- luminosité = 0.45 → floor(0.45 × 3) / 3 = floor(1.35) / 3 = 1 / 3 ≈ 0.33
- luminosité = 0.75 → floor(0.75 × 3) / 3 = floor(2.25) / 3 = 2 / 3 ≈ 0.67
- luminosité = 0.95 → floor(0.95 × 3) / 3 = floor(2.85) / 3 = 2 / 3 ≈ 0.67
```

## 3. Niveaux de détail

### Impact du nombre de niveaux (celLevels)

```
celLevels = 1          celLevels = 2         celLevels = 3
┌──────────┐          ┌──────┬───┐         ┌────┬────┬───┐
│████████░░│          │████░░│██░│         │███░│██░░│█░░│
│████████░░│          │████░░│██░│         │███░│██░░│█░░│
│████████░░│          │████░░│██░│         │███░│██░░│█░░│
│████████░░│          │████░░│██░░         │███░│██░░│█░░│
└──────────┘          └──────┴───┘         └────┴────┴───┘
Très cartoon           Cartoon              Cartoon+détail

celLevels = 5         celLevels = 8         Rendu lisse (∞)
┌─┬─┬─┬─┬─┐          ┌─┬─┬─┬─┬─┬─┬─┬─┐    ┌───────────────┐
│█│█│░│░│░│          │█│█│░│░│░│░│░│░│    │░░░░░░░░░░░░░░│
│█│█│░│░│░│          │█│█│░│░│░│░│░│░│    │░░░░░░░░░░░░░░│
│█│█│░│░│░│          │█│█│░│░│░░░░░│    │░░░░░░░░░░░░░░│
│█│█│░│░│░│          │█│█│░│░│░│░│░│░│    │░░░░░░░░░░░░░░│
└─┴─┴─┴─┴─┘          └─┴─┴─┴─┴─┴─┴─┴─┘    └───────────────┘
Très réaliste         Très réaliste         Lisse et naturel
```

## 4. Architecture du rendu

### Pipeline complet

```
┌─────────────────────────────────────────────┐
│ 1. DONNÉES DU MODÈLE                        │
│    - Position du vertex                      │
│    - Normale du vertex                       │
│    - Coordonnées de texture                  │
└──────────────────┬──────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────┐
│ 2. VERTEX SHADER                            │
│    - Transformation en espace écran          │
│    - Transformation des normales             │
│    - Passage des données au fragment shader  │
└──────────────────┬──────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────┐
│ 3. RASTERIZATION (GPU)                      │
│    - Conversion des triangles en pixels      │
│    - Interpolation des valeurs               │
└──────────────────┬──────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────┐
│ 4. FRAGMENT SHADER (CEL SHADING!)           │
│    a) Calcul éclairage Lambertien           │
│    b) Quantification (floor et division)     │
│    c) Application de la couleur              │
│    d) Calcul lumière ambiante                │
└──────────────────┬──────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────┐
│ 5. PIXEL FINAL                              │
│    Couleur cartoon / cel shading appliquée   │
└─────────────────────────────────────────────┘
```

## 5. Code GLSL simplifié

### Fragment Shader - Étapes détaillées

```glsl
void main() {
    // ÉTAPE 1: Normaliser la normale (importante!)
    vec3 norm = normalize(fragNormal);
    
    // ÉTAPE 2: Calculer la direction vers la lumière
    vec3 lightDir = normalize(lightPosition - fragPosition);
    
    // ÉTAPE 3: Calcul Lambertien (dot product)
    //          Retourne un nombre entre 0 et 1
    float diffuse = max(dot(norm, lightDir), 0.0);
    
    // ╭─────────────────────────────────────╮
    // │ ÉTAPE 4: QUANTIFICATION (CEL SHADING)  │
    // │ C'est ici que la magie se produit!    │
    // ╰─────────────────────────────────────╯
    float celShade = floor(diffuse * celLevels) / celLevels;
    
    // ÉTAPE 5: Appliquer la couleur
    vec3 baseColor = objectColor;
    vec3 diffuseColor = baseColor * celShade;
    
    // ÉTAPE 6: Ajouter lumière ambiante
    vec3 ambientColor = baseColor * 0.3;
    
    // ÉTAPE 7: Combiner et retourner
    vec3 finalColor = mix(ambientColor, diffuseColor, celShade);
    fragColor = vec4(finalColor, 1.0);
}
```

## 6. Variations et améliorations

### Cel Shading avec contours (Outline)

```
┌────────────┐          ┌────────────┐
│    ███    │          │▓▓███▓▓▓▓▓▓▓│
│   █████   │    →     │▓██████████▓│
│  ███████  │          │▓███████████│
│   █████   │          │▓██████████▓│
│    ███    │          │▓▓███▓▓▓▓▓▓▓│
└────────────┘          └────────────┘
Normal              Avec contours noirs
```

### Ajout de spécularité

```
Point faible sans         Avec reflets discrets
spécularité:
┌────────────┐          ┌────────────┐
│    ███    │          │    ███⚪    │
│   █████   │    →     │   █████    │
│  ███████  │          │  ███████   │
│   █████   │          │   █████    │
│    ███    │          │    ███     │
└────────────┘          └────────────┘
```

## 7. Applications pratiques

### Jeux vidéo utilisant le cel shading:

- **The Legend of Zelda: The Wind Waker** - Premier jeu grand public
- **Borderlands** - Série complète
- **Hi-Fi Rush** - Musique + cel shading
- **Persona 5** - Adaptation manga dynamique
- **XIII** - Comic book style

### Autres domaines:

- Animation 3D (films, séries)
- Visualization scientifique
- Publicité et marketing
- Architecture (présentation stylisée)
- Formation et éducation

## 8. Expériences à faire

1. **Modifier celLevels** - Observez le changement de style
2. **Bouger la lumière** - Voyez comment les bandes changent
3. **Changer de couleur** - Notez l'effet de saturation
4. **Augmenter résolution** - Plus de géométrie = meilleur détail
5. **Combiner avec textures** - Ajouter de la complexité visuelle

