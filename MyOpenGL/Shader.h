#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
protected:
	GLint index = -1;
	GLenum shaderType = GL_FRAGMENT_SHADER;

public:
	static std::string GetSource(std::string File);


	Shader();
	Shader(const GLenum& ShaderType);
	~Shader();

	// Methods
	GLint CompileSource(const std::string& Source);
	GLint CompileFile(const std::string& File);

	// Getters
	GLint GetIndex();

	// Debugging
	GLint GetLog(GLchar* InfoLog);
};

