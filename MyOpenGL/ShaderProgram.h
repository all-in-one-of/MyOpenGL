#pragma once

#include "Texture.h"
#include "Shader.h"

class ShaderProgram : public Object
{
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
	void SetFloat(const GLchar* Name, GLdouble Value) const; // Higher accuracy
	//void SetTextureSampler(const GLchar* Name, const Texture& Tex) const;


	// Getters
	GLint GetUniformLocation(const GLchar* Name) const;
};

