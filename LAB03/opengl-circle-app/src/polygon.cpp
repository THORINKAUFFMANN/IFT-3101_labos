#include "polygon.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

Polygon::Polygon(const std::vector<float>& coords, const std::vector<float>& rgba, float angle)
    : _coords(coords), _angle(angle), _rgba(rgba), vao(0), vbo(0)
{}

Polygon::~Polygon() {
    this->_coords.clear();
    this->_rgba.clear();
}

void Polygon::initialize() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Polygon::drawPolygon(const std::vector<float>& coords, float angle) {
    if (coords.size() < 6) return; // need at least 3 points (x,y)

    glColor4f(_rgba[0], _rgba[1], _rgba[2], _rgba[3]);

    glBegin(GL_POLYGON);
    for (size_t i = 0; i < coords.size(); i += 2) {
        float dx = coords[i];
        float dy = coords[i + 1];

        // Apply rotation around origin (0,0)
        float rotatedX = dx * cosf(angle) - dy * sinf(angle);
        float rotatedY = dx * sinf(angle) + dy * cosf(angle);

        glVertex2f(rotatedX, rotatedY);
    }
    glEnd();
}

void Polygon::render() {
    drawPolygon(_coords, _angle);
}