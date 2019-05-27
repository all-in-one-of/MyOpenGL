#pragma once

#include "Object.h"
#include "ShaderProgram.h"

class Camera : public Object
{
public:
	// Properties
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 transform = glm::mat4(1.0f);

	GLfloat aspect = 1.77777778f;
	GLfloat nearPlane = 0.1f;
	GLfloat farPlane = 100.0f;
	GLfloat fieldOfView = 65.0f;


	// Constructors & destructors
	Camera();
	~Camera();

	
	// Methods
	void Bind();
	void LookAt(const glm::vec3& Target);
	void SetAspect(const GLuint& Width, const GLuint& Height);


	// Getters
	glm::mat4 GetProjectionMatrix() const;
};

