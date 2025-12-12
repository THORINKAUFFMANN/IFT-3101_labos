# Instructions de compilation et exécution

## Prérequis

- **openFrameworks** installé
- **g++** ou compilateur compatible
- **make**
- GPU compatible avec OpenGL 3.0+

## Structure du projet

```
Lab13/
├── src/
│   ├── main.cpp
│   ├── ofApp.h
│   └── ofApp.cpp
├── bin/
│   └── data/
│       └── shaders/
│           ├── celShading.vert
│           └── celShading.frag
├── Makefile
├── config.make
└── addons.make
```

## Compilation

### Sur Linux/macOS

1. Placez-vous dans le répertoire du projet:
```bash
cd Lab13
```

2. Compilez avec:
```bash
make
```

3. Exécutez:
```bash
./bin/Lab13
```

### Sur Windows

1. Ouvrez `Lab13.code-workspace` dans VS Code
2. Utilisez la tâche de compilation VS Code
3. Ou compilez manuellement avec le générateur approprié

## Dépannage

### Erreur: "Shaders not found"
- Assurez-vous que les fichiers de shader sont dans `bin/data/shaders/`
- Les chemins doivent être relatifs au répertoire `bin/`

### Erreur de compilation liée à OpenGL
- Vérifiez que votre GPU supporte au moins OpenGL 3.0
- Assurez-vous que les drivers sont à jour

### Performance lente
- Réduisez la résolution des objets (setResolution())
- Réduisez la résolution de la fenêtre dans main.cpp
- Diminuez la fréquence d'image (ofSetFrameRate)

## Fichiers de shader

Les shaders sont automatiquement compilés à la première exécution. Si vous les modifiez:

1. Les changements seront pris en compte à la prochaine exécution
2. Aucune recompilation C++ n'est nécessaire
3. Les shaders sont interprétés par votre GPU

## Points clés du code

### Chargement des shaders (ofApp::setup)
```cpp
celShader.load("shaders/celShading.vert", "shaders/celShading.frag");
```

### Application des shaders (ofApp::draw)
```cpp
celShader.begin();
// ... dessiner les objets ...
celShader.end();
```

### Passage de paramètres
```cpp
celShader.setUniform3f("lightPosition", x, y, z);
celShader.setUniform1f("celLevels", 3.0f);
```
