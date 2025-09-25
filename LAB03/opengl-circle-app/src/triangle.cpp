#include "triangle.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

Triangle::Triangle(float x, float y, float base, float height, float angle, const std::vector<float>& rgba)
    : _base(base), _height(height), _pos({x, y}), _angle(angle), _rgba(rgba), vao(0), vbo(0)
{}

Triangle::~Triangle() {
    this->_pos.clear();
    this->_rgba.clear();
}

void Triangle::initialize() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Triangle::drawTriangle(float x, float y, float base, float height, float angle) {
    glColor4f(_rgba[0], _rgba[1], _rgba[2], _rgba[3]);

    // Define vertices for an isosceles triangle centered on (x, y)
    float halfBase = base / 2.0f;

    float vertices[3][2] = {
        {0.0f, height / 2.0f},    // top
        {-halfBase, -height / 2.0f}, // bottom-left
        {halfBase, -height / 2.0f}   // bottom-right
    };

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        // Apply rotation
        float dx = vertices[i][0];
        float dy = vertices[i][1];

        float rotatedX = dx * cosf(angle) - dy * sinf(angle);
        float rotatedY = dx * sinf(angle) + dy * cosf(angle);

        glVertex2f(x + rotatedX, y + rotatedY);
    }
    glEnd();
}

void Triangle::render() {
    drawTriangle(_pos[0], _pos[1], _base, _height, _angle);
}
