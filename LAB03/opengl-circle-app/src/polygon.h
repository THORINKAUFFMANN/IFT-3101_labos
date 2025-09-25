#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

class Polygon {
public:
    // coords = {x1, y1, x2, y2, x3, y3, ...}
    Polygon(const std::vector<float>& coords, const std::vector<float>& rgba, float angle = 0.0f);
    ~Polygon();

    void initialize();
    void render();

private:
    void drawPolygon(const std::vector<float>& coords, float angle);

    std::vector<float> _coords; // flat list of x,y pairs
    float _angle;
    std::vector<float> _rgba;
    unsigned int vao, vbo;
};

#endif
