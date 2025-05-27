#pragma once
#include <string>
#include <GL/glew.h>

GLuint CompileShader(GLenum type, const std::string& source);
GLuint CreateShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);