#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();
    bool initialize();
    void update();
    bool shouldClose();
    void terminate();

private:
    const char* title;
    int width;
    int height;
    GLFWwindow* window;
};

#endif // WINDOW_H