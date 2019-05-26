#pragma once

#include "Object.h"
#include "ShaderProgram.h"

#include <vector>


class Primitive : public Object
{
private:
	/*glm::vec3 points[];
	glm::vec3 normals[];
	glm::vec3 colours[];
	glm::vec2 texCoords[];*/

	//std::vector<GLfloat> vertices;
	//std::vector<GLuint> indices;

	GLuint VBO, VAO, EBO;


public:

	// Properties
	glm::mat4 transform = glm::mat4(1.0f);

	Primitive();
	~Primitive();


	// Methods
	void Construct();
	void Draw();
	void Destroy();


	// Getters
	GLuint GetVBO() const;
	GLuint GetVAO() const;
	GLuint GetEBO() const;
};

