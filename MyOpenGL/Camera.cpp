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

	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(trans, transform.scale, transform.rotation, transform.position, skew, perspective);
}

void Camera::SetAspect(const GLuint & Width, const GLuint & Height)
{
	aspect = (GLfloat)Width / (GLfloat)Height;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(fieldOfView), aspect, nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix() const
{
	/*glm::mat4 r = glm::toMat4(rotation);
	glm::mat4 p = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 s = glm::scale(glm::mat4(1.0f), scale);

	return p * r * glm::mat4(1.0f);*/

	//return glm::lookAt(position, position + GetForward(), GetUp());
	return transform.GetMatrix();
}
