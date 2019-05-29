#include "EditorCamera.h"



EditorCamera::EditorCamera()
{
}


EditorCamera::~EditorCamera()
{
}

void EditorCamera::Update(const float& DeltaTime)
{
	GLFWwindow* window = Window::GetCurrent();
	if (window == nullptr)
		return;

	glm::vec3 forward = GetForward();
	glm::vec3 right = GetRight();
	glm::vec3 up = GetUp();

	float s = glfwGetKey(Window::GetCurrent(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? speed * shiftMultiplier : speed;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		transform.position += forward * DeltaTime * s;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		transform.position -= forward *DeltaTime * s;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		transform.position -= right * DeltaTime * s;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		transform.position += right * DeltaTime * s;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		transform.position += up * DeltaTime * s;
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		transform.position -= up *DeltaTime * s;
}
