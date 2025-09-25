#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vector"

class Ellipse {
    public:
        Ellipse(float x, float y, float radiusX, float radiusY, float angle, const std::vector<float>& rgba);
        ~Ellipse();
        
        void initialize();
        void render();
        void drawCircle(float x, float y, float radiusX, float radiusY, float angle, int numSegments);
    private:
        float _angle;
        float _radiusX;
        float _radiusY;;
        std::vector<float> _rgba;
        std::vector<float> _pos;
        
        // OpenGL-related settings
        GLuint vao, vbo;
};