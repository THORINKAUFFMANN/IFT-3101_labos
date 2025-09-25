#include "ellipse.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

// Add these lines if you declared them in ellipse.h
Ellipse::Ellipse(float x, float y, float radiusX, float radiusY, float angle, const std::vector<float>& rgba)
    : _radiusX(radiusX), _radiusY(radiusY), _pos({x, y}), _angle(angle), _rgba(rgba), vao(0), vbo(0)
{}

Ellipse::~Ellipse() {
    this->_pos.clear();
    this->_rgba.clear();
}

void Ellipse::initialize() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Ellipse::drawCircle(float x, float y, float radiusX, float radiusY, float angle, int numSegments) {
    glColor4f(_rgba[0], _rgba[1], _rgba[2], _rgba[3]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        // Ellipse parametric equation
        float dx = radiusX * cosf(theta);
        float dy = radiusY * sinf(theta);
        // Rotate by angle
        float rotatedX = dx * cosf(angle) - dy * sinf(angle);
        float rotatedY = dx * sinf(angle) + dy * cosf(angle);
        glVertex2f(x + rotatedX, y + rotatedY);
    }
    glEnd();
}

void Ellipse::render() {
    drawCircle(_pos[0], _pos[1], _radiusX, _radiusY, _angle, 100);
}