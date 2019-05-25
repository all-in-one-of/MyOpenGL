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
	ShaderProgram(const std::string& Folder);
	~ShaderProgram();


	// Methods
	GLint CompileShadersFromFolder(const std::string& Folder);
	GLint LinkShaders();
	void Bind();
	void Unbind();

	// Setters
	void SetBool(const GLchar* Name, GLboolean Value) const;
	void SetInt(const GLchar* Name, GLint Value) const;
	void SetFloat(const GLchar* Name, GLfloat Value) const;


	// Getters
	GLint GetIndex() const;
	GLboolean IsValid() const;
	GLint GetUniformLocation(const GLchar* Name) const;
};

