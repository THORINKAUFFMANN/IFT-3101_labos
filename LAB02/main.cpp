#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Add this global variable at the top (before main)
static bool save_requested = false;

// Add this function before main()
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

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL Image", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Set the key callback
    glfwSetKeyCallback(window, key_callback);

    // Set viewport to match window size
    int win_width, win_height;
    glfwGetFramebufferSize(window, &win_width, &win_height);
    glViewport(0, 0, win_width, win_height);

    // Set up orthographic projection to match window aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)win_width / (float)win_height;
    float ortho_half = 10.0f;
    if (aspect >= 1.0f) {
        // Wide window
        glOrtho(-ortho_half * aspect, ortho_half * aspect, -ortho_half, ortho_half, -1.0, 1.0);
    } else {
        // Tall window
        glOrtho(-ortho_half, ortho_half, -ortho_half / aspect, ortho_half / aspect, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }
    // List of image paths
    std::vector<const char*> images_path = {"red-cover.png", "epic-cover.jpg", "loud-cover.jpg", "arcane-cover.jpg", "maneskin-cover.jpg", "reno-cover.jpeg", "caravan-cover.jpg", "poor-cover.jpg", "vald-cover.jpg"};

    std::vector<std::vector<GLfloat>> image_positions = {
        {-10.0f, 10.0f, 0.0f},   // red-cover.png
        {-3.0f, 10.0f, 0.0f},   // epic-cover.jpg
        {4.0f, 10.0f, 0.0f},    // loud-cover.jpg
        {-10.0f, 3.0f, 0.0f},     // arcane-cover.jpg
        {-3.0f, 3.0f, 0.0f} ,    // maneskin-cover.jpg
        {4.0f, 3.0f, 0.0f},     // reno-cover.jpeg
        {-10.0f, -4.0f, 0.0f},    // caravan-cover.jpg
        {-3.0f, -4.0f, 0.0f},    // poor-cover.jpg
        {4.0f, -4.0f, 0.0f}    // vald-cover.jpg
    };
    std::vector<int> widths, heights;
    int width, height, channels;
    std::vector<GLuint> textures;
    for (size_t i = 0; i < images_path.size(); i++) {
        unsigned char* data = stbi_load(images_path.at(i), &width, &height, &channels, 4);
        if (!data) {
            std::cerr << "Failed to load image" << images_path.at(i) << std::endl;
            return -1;
        } else {
            std::cout << images_path.at(i) << ": Image loaded" << std::endl;
        }
        // Create texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        textures.push_back(texture);

        // Store width and height for this image
        widths.push_back(width);
        heights.push_back(height);

        // Upload image to texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free image memory
        stbi_image_free(data);
    }
    
    float pixels_per_unit = 40.0f; // 800px window / 20 units = 40 px/unit

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        for (size_t i = 0; i < textures.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, textures.at(i));

            float scale = 0.4f;
            float quad_width = (widths[i] / pixels_per_unit) * scale;
            float quad_height = (heights[i] / pixels_per_unit) * scale;

            // Center the quad at the given position
            std::vector<GLfloat> pos = image_positions[i];

            glPushMatrix();
                glTranslatef(pos[0] + quad_width / 2.0f, pos[1] - quad_height / 2.0f, pos[2]);

                float half_width = quad_width / 2.0f;
                float half_height = quad_height / 2.0f;

                glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 1.0f); glVertex2f(-half_width, -half_height);
                    glTexCoord2f(1.0f, 1.0f); glVertex2f( half_width, -half_height);
                    glTexCoord2f(1.0f, 0.0f); glVertex2f( half_width,  half_height);
                    glTexCoord2f(0.0f, 0.0f); glVertex2f(-half_width,  half_height);
                glEnd();
            glPopMatrix();
        }

        if (save_requested) {
            save_screenshot("output.png", win_width, win_height);
            std::cout << "Screenshot saved as output.png" << std::endl;
            save_requested = false;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    GLuint texture;
    for (size_t i = 0; i < textures.size(); i++) {
        texture = textures.at(i);
        glDeleteTextures(1, &texture);
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
