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
		shaderProgram->SetViewMatrix(GetViewMatrix());
		shaderProgram->SetProjectionMatrix(GetProjectionMatrix());
	}
}

void Camera::LookAt(const glm::vec3 & Target)
{
	glm::mat4 trans = glm::lookAt(transform.position, Target, worldUp);

	glm::vec3 s;
	glm::quat r;
	glm::vec3 p;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(trans, s, r, p, skew, perspective);

	transform.rotation = r;
}

void Camera::SetAspect(const GLuint & Width, const GLuint & Height)
{
	aspect = (GLfloat)Width / (GLfloat)Height;
}

glm::vec3 Camera::GetForward() const
{
	return -transform.GetForward();
}

glm::vec3 Camera::GetRight() const
{
	return transform.GetRight();
}

glm::vec3 Camera::GetUp() const
{
	return transform.GetUp();
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(fieldOfView), aspect, nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(transform.position, transform.position - transform.GetForward(), transform.GetUp()); // Always face opposite direction of forward vec
}
