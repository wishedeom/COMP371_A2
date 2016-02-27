#pragma once
#include "glew.h"
#include <string>
#include "gtc/matrix_transform.hpp"	// Matrix types

// Manages everyhting to do with OpenGL shaders.
// Reads the source code from a text file, compiles and links the shaders, makes the shader program,
// and allows the shader program to be used with a specific transformation matrix.
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