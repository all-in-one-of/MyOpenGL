#include "Camera.h"

Camera* Camera::current = nullptr;

void Camera::UpdateRotation()
{
	transform.rotation = glm::quat(glm::radians(glm::vec3(pitch, yaw, roll))); // Re-create rotation
}

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Bind()
{
	Camera::current = this; // Point to this camera to draw with
}

void Camera::Draw()
{
	Shader* shaderProgram = Shader::GetCurrent();
	if (shaderProgram != nullptr && shaderProgram->IsValid())
	{
		shaderProgram->SetViewMatrix(GetViewMatrix());
		shaderProgram->SetProjectionMatrix(GetProjectionMatrix());
		shaderProgram->SetCameraPosition(transform.position);
		shaderProgram->SetCameraDirection(GetForward());
	}
}

void Camera::LookAt(const glm::vec3 & Target)
{
	UpdateRotation();
	glm::mat4 trans = glm::lookAt(transform.position, Target, worldUp);

	glm::vec3 s;
	glm::quat r;
	glm::vec3 p;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(trans, s, r, p, skew, perspective);

	transform.rotation = r;
}

glm::vec3 Camera::GetForward()
{
	UpdateRotation();
	return -transform.GetForward();
}

glm::vec3 Camera::GetRight()
{
	UpdateRotation();
	return transform.GetRight();
}

glm::vec3 Camera::GetUp()
{
	UpdateRotation();
	return transform.GetUp();
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	GLfloat aspect;

	Window* window = Window::GetCurrentObject();
	if (window != nullptr)
	{
		glm::ivec2 size = window->GetSize();
		aspect = (GLfloat)size.x / (GLfloat)size.y;
	}
	else
		aspect = 1920.0f / 1080.0f;


	return glm::perspective(glm::radians(fieldOfView), aspect, nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
	UpdateRotation();
	return glm::lookAt(transform.position, transform.position - transform.GetForward(), transform.GetUp()); // Always face opposite direction of forward vec
}

Camera * Camera::GetCurrent()
{
	return Camera::current;
}
