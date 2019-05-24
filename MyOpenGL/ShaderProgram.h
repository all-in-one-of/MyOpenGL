#pragma once

#include "Shader.h"

class ShaderProgram
{
private:
	GLint index = -1;


public:
	Shader vertexShader, fragmentShader;

	// Constructors & destructors
	ShaderProgram();
	~ShaderProgram();


	// Methods
	GLint CompileShadersFromFolder(const std::string& Folder);
	GLint LinkShaders();
	void Bind();
	void Unbind();


	// Getters
	GLint GetIndex();
};

