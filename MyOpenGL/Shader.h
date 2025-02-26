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
#include "Camera.h"

#include <set>
#include <algorithm>


class Shader : public Object
{
private:
	static Shader* current;
	static std::set<Shader*> all;
	void Create();

public:

	// Compiler constants
	const GLchar* MODEL_MATRIX = "Model";
	const GLchar* VIEW_MATRIX = "View";
	const GLchar* PROJECTION_MATRIX = "Projection";


	// Properties
	SubShader vertexShader, fragmentShader; // All sub-shaders
	std::string source;


	// Constructors & destructors
	Shader();
	Shader(const std::string& Folder);
	~Shader();
	

	// Methods
	GLint CompileShadersFromFolder(const std::string& Folder);
	GLint LinkShaders();
	GLint Compile(const std::string& Folder);
	GLint Recompile();
	static void RecompileAll();
	void Bind();
	void Destroy();
	static void Cleanup();


	// Setters
	void SetBool(const GLchar* Name, const GLboolean& Value) const;
	void SetInt(const GLchar* Name, const GLint& Value) const;
	void SetFloat(const GLchar* Name, const GLfloat& Value) const;
	void SetVec3(const GLchar* Name, const glm::vec3& Value) const;
	void SetVec4(const GLchar* Name, const glm::vec4& Value) const;
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
	static void Unbind(); // Call at the end of the render thread
};

