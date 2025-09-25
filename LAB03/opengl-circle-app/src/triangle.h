#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

class Triangle {
public:
    Triangle(float x, float y, float base, float height, float angle, const std::vector<float>& rgba);
    ~Triangle();

    void initialize();
    void render();

private:
    void drawTriangle(float x, float y, float base, float height, float angle);

    float _base;
    float _height;
    std::vector<float> _pos;
    float _angle;
    std::vector<float> _rgba;
    unsigned int vao, vbo;
};

#endif
