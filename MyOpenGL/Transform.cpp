#include "Transform.h"



Transform::Transform()
{
}


Transform::~Transform()
{
}

glm::vec3 Transform::GetForward() const
{
	return glm::vec3(0.0f, 0.0f, -1.0f) * rotation;
}

glm::vec3 Transform::GetUp() const
{
	return glm::vec3(0.0f, 1.0f, 0.0f) * rotation;
}

glm::vec3 Transform::GetRight() const
{
	return glm::normalize(glm::cross(GetForward(), GetUp()));
}

glm::mat4 Transform::GetMatrix() const
{
	return glm::lookAt(position, position + GetForward(), GetUp());
}
