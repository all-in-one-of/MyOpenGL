#pragma once

// GLM Mathematics library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include "glm/gtx/string_cast.hpp"

class Transform
{
public:
	// Constants
	static const glm::vec3 WORLD_FORWARD;// = glm::vec3(0.0, 0.0, 1.0f);
	static const glm::vec3 WORLD_RIGHT;// = glm::vec3(1.0f, 0.0f, 0.0f);
	static const glm::vec3 WORLD_UP;// = glm::vec3(0.0f, 1.0f, 0.0f);


	// Properties
	glm::vec3 position = glm::vec3(0.0f);
	glm::quat rotation;
	glm::vec3 scale = glm::vec3(1.0f);

	Transform();
	~Transform();

	// Getters
	glm::vec3 GetForward() const;
	glm::vec3 GetUp() const;
	glm::vec3 GetRight() const;
	glm::mat4 GetMatrix() const;
	glm::mat4 GetMatrixWithoutScale() const;
};

