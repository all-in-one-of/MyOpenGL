#pragma once

// GLM Mathematics library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include "glm/gtx/string_cast.hpp"


#include "Texture.h"
#include "SubShader.h"


class Shader : public Object
{
private:
	static Shader* current;

public:

	// Compiler constants
	const GLchar* MODEL_MATRIX = "Model";
	const GLchar* VIEW_MATRIX = "View";
	const GLchar* PROJECTION_MATRIX = "Projection";


	// Shaders
	SubShader vertexShader, fragmentShader;


	// Constructors & destructors
	Shader();
	Shader(const std::string& Folder);
	~Shader();


	// Methods
	GLint CompileShadersFromFolder(const std::string& Folder);
	GLint LinkShaders();
	void Bind();
	void Unbind();


	// Setters
	void SetBool(const GLchar* Name, const GLboolean& Value) const;
	void SetInt(const GLchar* Name, const GLint& Value) const;
	void SetFloat(const GLchar* Name, const GLfloat& Value) const;
	void SetVec3(const GLchar* Name, const glm::vec3& Value) const;
	void SetMatrix4x4(const GLchar* Name, const glm::mat4& Value) const;
	//void SetTextureSampler(const GLchar* Name, const Texture& Tex) const;


	// Matrices
	void SetModelMatrix(const glm::mat4& Model) const;
	void SetViewMatrix(const glm::mat4& View) const;
	void SetProjectionMatrix(const glm::mat4& Projection) const;
	void SetCameraPosition(const glm::vec3& ViewPosition) const;
	void SetCameraDirection(const glm::vec3& ViewDirection) const;


	// Getters
	GLint GetUniformLocation(const GLchar* Name) const;
	static Shader* GetCurrent();
};

