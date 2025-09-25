#ifndef TEXT_H
#define TEXT_H

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

// Struct for a single glyph
struct Character {
    GLuint textureID;   // ID of the glyph texture
    glm::ivec2 size;    // Size of glyph
    glm::ivec2 bearing; // Offset from baseline to left/top of glyph
    GLuint advance;     // Offset to advance to next glyph
};

class TextRenderer {
public:
    TextRenderer(const std::string& fontPath, int fontSize, const std::vector<float>& rgba);
    ~TextRenderer();

    // Now pass window width, height, and shader ID
    void initialize(int windowWidth, int windowHeight, GLuint shaderID);
    void renderText(const std::string& text, float x, float y, float scale);

private:
    void loadFont();

    std::map<char, Character> Characters;
    GLuint VAO, VBO;
    std::vector<float> _rgba;
    std::string _fontPath;
    int _fontSize;
    GLuint _shaderID;  // <--- store shader
};

#endif
