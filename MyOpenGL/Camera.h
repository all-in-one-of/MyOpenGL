#pragma once

#include "Window.h"
#include "Object.h"
#include "Transform.h"
#include "ShaderProgram.h"


class Camera : public Object
{
private:
	void UpdateRotation();

public:
	// Properties
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Transform transform;
	GLfloat nearPlane = 0.1f;
	GLfloat farPlane = 100.0f;
	GLfloat fieldOfView = 65.0f;

	float yaw = 0.0f, pitch = 0.0f, roll = 0.0f; // We control the quaternion rotation directly from yaw, pitch, and roll. This is more suitable for controlling a camera.


	// Constructors & destructors
	Camera();
	~Camera();

	
	// Methods
	void Bind();
	void LookAt(const glm::vec3& Target);


	// Getters
	glm::vec3 GetForward();
	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewMatrix();
};

