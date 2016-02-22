#pragma once

#include "glew.h"
#include <string>
#include "gtc/matrix_transform.hpp"	// Matrix types

class Shader
{
	GLuint programID;
	GLuint transformationMatrixID;
	
	static std::string readSourceCode (const std::string path);
	static GLuint compileShader (const std::string path, const GLenum shaderType);
	static GLuint makeShaderProgram (const std::string vertexShaderPath, const std::string fragmentShaderPath);

public:
	
	// Constructors
	Shader();
	Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath);

	// Accessors
	GLuint program() const;

	// To use shader program in draw loop
	void Shader::use(const glm::mat4& transformationMatrix) const;
};