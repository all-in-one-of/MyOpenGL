#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Object.h"

class Shader : public Object
{
protected:
	GLenum shaderType = GL_FRAGMENT_SHADER;

public:
	static std::string GetSource(std::string File);


	Shader();
	Shader(const GLenum& ShaderType);
	~Shader();


	// Methods
	GLint CompileSource(const std::string& Source);
	GLint CompileFile(const std::string& File);


	// Debugging
	GLint GetLog(GLchar* InfoLog);
	std::string GetShaderType();
};

