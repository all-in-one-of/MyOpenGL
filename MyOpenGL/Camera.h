#pragma once

#include "Object.h"
#include "Transform.h"
#include "ShaderProgram.h"

class Camera : public Object
{
public:
	// Properties
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Transform transform;
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
	glm::vec3 GetForward() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewMatrix() const;
};

