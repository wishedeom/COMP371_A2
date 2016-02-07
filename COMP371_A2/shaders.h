#pragma once

#include "glew.h"
#include <string>

std::string readSourceCode(const std::string path);
GLuint compileShader(const std::string path, const GLenum shaderType);
GLuint makeShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath);