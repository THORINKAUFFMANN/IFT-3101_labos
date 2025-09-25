#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "ellipse.h"
#include "triangle.h"
#include "polygon.h"
#include "text.h"
#include "shader_utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
static bool save_requested = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-1, 1, -1, 1, -1, 1);
    glOrtho(0, width, height, 0, -1, 1); // Set the coordinate system to match the window size
    glMatrixMode(GL_MODELVIEW);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        save_requested = true;
    }
}

void save_screenshot(const char* filename, int width, int height) {
    std::vector<unsigned char> pixels(width * height * 3);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_BACK);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // Flip vertically (OpenGL's origin is bottom-left, PNG expects top-left)
    std::vector<unsigned char> flipped(width * height * 3);
    for (int y = 0; y < height; ++y) {
        memcpy(&flipped[y * width * 3],
               &pixels[(height - 1 - y) * width * 3],
               width * 3);
    }

    stbi_write_png(filename, width, height, 3, flipped.data(), width * 3);
}

std::string readShaderFile(const std::string& filePath) {
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        return "";
    }
}
void renderText(float x, float y, const char* string, void *font) {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c); // Or another suitable bitmap font
    }
}

int main(int argc, char **argv) {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }
    glutInit(&argc, argv);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Labo 3", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        return -1;
    }

    //* ellipses
    std::vector<Ellipse> ellipses;
    // args: radiusX, radiusY, x, y, angle, rba
    ellipses.emplace_back( 270, 735, 50, 120, 0.55f, std::vector<float>{0.38f, 0.084f, 0.0f, 1.0f});
    ellipses.emplace_back( 160, 750, 50, 120, -0.80f, std::vector<float>{0.38f, 0.084f, 0.0f, 1.0f});
    ellipses.emplace_back( 250, 635, 50, 120, 0.40f, std::vector<float>{0.58f, 0.074f, 0.0f, 1.0f});
    ellipses.emplace_back( 140, 650, 50, 120, -0.70f, std::vector<float>{0.58f, 0.074f, 0.0f, 1.0f});
    ellipses.emplace_back( 250, 535, 50, 120, 0.55f, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    ellipses.emplace_back( 145, 540, 50, 120, -0.65f, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    ellipses.emplace_back( 250, 435, 50, 120, 0.7f, std::vector<float>{1.0f, 0.47f, 0.047f, 1.0f});
    ellipses.emplace_back( 140, 420, 50, 120, -0.4f, std::vector<float>{1.0f, 0.47f, 0.047f, 1.0f});
    ellipses.emplace_back( 270, 350, 50, 120, 1.0f, std::vector<float>{0.86f, 0.75f, 0.0f, 1.0f});
    ellipses.emplace_back( 150, 315, 50, 120, -0.5f, std::vector<float>{0.86f, 0.75f, 0.0f, 1.0f});
    ellipses.emplace_back( 290, 270, 50, 120, 1.2f, std::vector<float>{0.86f, 0.85f, 0.0f, 1.0f});
    ellipses.emplace_back( 180, 215, 50, 120, -0.3f, std::vector<float>{0.86f, 0.85f, 0.0f, 1.0f});
    ellipses.emplace_back( 250, 200, 50, 120, 0.5f, std::vector<float>{0.86f, 0.85f, 0.0f, 1.0f});
    // args: radiusX, radiusY, x, y, angle, rgba
    ellipses.emplace_back( 970, 735, 50, 120, -0.55f, std::vector<float>{0.38f, 0.084f, 0.0f, 1.0f});
    ellipses.emplace_back( 1080, 750, 50, 120, 0.80f, std::vector<float>{0.38f, 0.084f, 0.0f, 1.0f});
    ellipses.emplace_back( 990, 635, 50, 120, -0.40f, std::vector<float>{0.58f, 0.074f, 0.0f, 1.0f});
    ellipses.emplace_back( 1100, 650, 50, 120, 0.70f, std::vector<float>{0.58f, 0.074f, 0.0f, 1.0f});
    ellipses.emplace_back( 990, 535, 50, 120, -0.55f, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    ellipses.emplace_back( 1095, 540, 50, 120, 0.65f, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    ellipses.emplace_back( 990, 435, 50, 120, -0.70f, std::vector<float>{1.0f, 0.47f, 0.047f, 1.0f});
    ellipses.emplace_back( 1100, 420, 50, 120, 0.40f, std::vector<float>{1.0f, 0.47f, 0.047f, 1.0f});
    ellipses.emplace_back( 970, 350, 50, 120, -1.0f, std::vector<float>{0.86f, 0.75f, 0.0f, 1.0f});
    ellipses.emplace_back( 1090, 315, 50, 120, 0.50f, std::vector<float>{0.86f, 0.75f, 0.0f, 1.0f});
    ellipses.emplace_back( 950, 270, 50, 120, -1.2f, std::vector<float>{0.86f, 0.85f, 0.0f, 1.0f});
    ellipses.emplace_back( 1060, 215, 50, 120, 0.30f, std::vector<float>{0.86f, 0.85f, 0.0f, 1.0f});
    ellipses.emplace_back( 990, 200, 50, 120, -0.50f, std::vector<float>{0.86f, 0.85f, 0.0f, 1.0f});

    //* triangles
    std::vector<Triangle> triangles;
    triangles.emplace_back( 500, 300, 80, 400, 3.14f, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    triangles.emplace_back( 700, 300, 80, 400, 3.14f, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});

    std::vector<float> coords1 = {
        650, 650,   // bottom-left
        800, 650,   // bottom-right
        540, 500,   // top-right
        462, 500    // top-left
    };
    std::vector<float> coords2 = {
        425, 650,   // bottom-left
        575, 650,   // bottom-right
        740, 500,   // top-right
        660, 500    // top-left
    };
    std::vector<float> coords3 = {
        625, 850,   // bottom-left
        600, 850,   // bottom-right
        650, 650,   // top-right
        800, 650    // top-left
    };
    std::vector<float> coords4 = {
        625, 825,   // bottom-left
        600, 850,   // bottom-right
        425, 650,   // top-right
        575, 650    // top-left
    };
    std::vector<Polygon> polygones;
    polygones.emplace_back(coords1, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    polygones.emplace_back(coords2, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    polygones.emplace_back(coords4, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    polygones.emplace_back(coords3, std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
    
    int width, height;
    
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (auto& ellipse : ellipses) {
            ellipse.render();
        }
        for (auto& triangle : triangles) {
            triangle.render();
        }
        for (auto& polygon : polygones) {
            polygon.render();
        }
        renderText(550, 100, "ZAGREUS", GLUT_BITMAP_TIMES_ROMAN_24);
        renderText(550, 130, "son of Hades", GLUT_BITMAP_HELVETICA_18);

        if (save_requested) {
            save_screenshot("output.png", WIDTH, HEIGHT);
            std::cout << "Screenshot saved as output.png" << std::endl;
            save_requested = false;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}