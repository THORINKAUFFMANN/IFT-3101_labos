#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include <GL/glew.h>
#include <string>

// Load vertex + fragment shader from file and link them into a program
GLuint LoadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path);

#endif
