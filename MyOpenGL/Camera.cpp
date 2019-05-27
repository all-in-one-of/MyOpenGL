#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Bind()
{
	ShaderProgram* shaderProgram = ShaderProgram::GetCurrent();
	if (shaderProgram != nullptr && shaderProgram->IsValid())
	{
		shaderProgram->SetViewMatrix(transform);
		shaderProgram->SetProjectionMatrix(GetProjectionMatrix());
	}
}

void Camera::LookAt(const glm::vec3 & Target)
{
	transform = glm::lookAt(glm::vec3(transform[3]), Target, worldUp);;
}

void Camera::SetAspect(const GLuint & Width, const GLuint & Height)
{
	aspect = (GLfloat)Width / (GLfloat)Height;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(fieldOfView), aspect, nearPlane, farPlane);
}
