#pragma once

// GLM Mathematics library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
	void SetBool(const GLchar* Name, const GLboolean& Value) const;
	void SetInt(const GLchar* Name, const GLint& Value) const;
	void SetFloat(const GLchar* Name, const GLfloat& Value) const;
	void SetMatrix4x4(const GLchar* Name, const glm::mat4& Value) const;
	//void SetTextureSampler(const GLchar* Name, const Texture& Tex) const;


	// Getters
	GLint GetUniformLocation(const GLchar* Name) const;
};

