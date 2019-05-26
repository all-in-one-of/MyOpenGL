#include "Primitive.h"



Primitive::Primitive()
{
}


Primitive::~Primitive()
{
	Destroy();
}

void Primitive::Construct()
{
	GLfloat vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	GLuint indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Generate vertex attribute array object & buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // Buffer for vertices
	glGenBuffers(1, &EBO); // Buffer for indices (element buffer)

	glBindVertexArray(VAO);


	// Bind vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind indices buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Attributes
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void Primitive::Draw()
{
	ShaderProgram* shaderProgram = ShaderProgram::GetCurrent();
	if (shaderProgram->IsValid())
	{
		shaderProgram->SetModelMatrix(transform);
	}

	// render container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Consolidate me for variable size
}

void Primitive::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

GLuint Primitive::GetVBO() const
{
	return VBO;
}

GLuint Primitive::GetVAO() const
{
	return VAO;
}

GLuint Primitive::GetEBO() const
{
	return EBO;
}