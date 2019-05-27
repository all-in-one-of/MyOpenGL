#include "Primitive.h"



std::vector<GLfloat> Primitive::GetRawVertices() const
{
	std::vector<GLfloat> rawVertices;

	for (int i = 0; i < vertices.size(); i++)
	{
		Vertex v = vertices[i];

		// Position
		rawVertices.push_back(v.position.x);
		rawVertices.push_back(v.position.y);
		rawVertices.push_back(v.position.z);

		// TexCoords
		rawVertices.push_back(v.texCoord.x); // U
		rawVertices.push_back(v.texCoord.y); // V
	}

	return rawVertices;
}

Primitive::Primitive()
{
}


Primitive::~Primitive()
{
	Destroy();
}

void Primitive::Construct()
{
	// Convert vectors to array data
	std::vector<GLfloat> rawVertices = GetRawVertices(); // Get raw vertex data as list of floats
	GLfloat* rawVerticesPt = rawVertices.data();		 // Convert list of floats to array (pointer to memory). We don't know the size of this without the vector.
	GLuint* indicesPt = indices.data();					 // Convert list of uints to array


	// Generate vertex attribute array object & buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // Buffer for vertices
	glBindVertexArray(VAO);

	// EBO (indices)
	if (drawMode == DrawMode::DrawElements)
	{
		glGenBuffers(1, &EBO); // Buffer for indices (element buffer)

		// Bind indices buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indicesPt, GL_STATIC_DRAW);
	}

	

	// Bind vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * rawVertices.size(), rawVerticesPt, GL_STATIC_DRAW);


	// Attributes
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0); // change me
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // change me
	glEnableVertexAttribArray(1);
}

void Primitive::Draw(const glm::mat4& Transform)
{
	ShaderProgram* shaderProgram = ShaderProgram::GetCurrent();
	if (shaderProgram != nullptr && shaderProgram->IsValid())
	{
		shaderProgram->SetModelMatrix(Transform);
	}

	// render container
	glBindVertexArray(VAO);
	
	// Allow for drawing without EBO
	switch (drawMode)
	{
	case Primitive::DrawMode::DrawElements:
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // Consolidate me for variable size
		break;
	default:
	case Primitive::DrawMode::DrawArrays:
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		break;
	}
}

void Primitive::Draw()
{
	Draw(transform);
}

void Primitive::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Primitive::AddVertex(const Vertex & NewVertex)
{
	vertices.push_back(NewVertex);
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