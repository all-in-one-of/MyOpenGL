#include "Primitive.h"



std::vector<GLfloat> Primitive::GetRawVertices() const
{
	std::vector<GLfloat> rawVertices;

	// Lambdas
	auto AddVec3 = [&] (glm::vec3 v)
	{
		rawVertices.push_back(v.x);
		rawVertices.push_back(v.y);
		rawVertices.push_back(v.z);
	};

	auto AddVec2 = [&](glm::vec2 v)
	{
		rawVertices.push_back(v.x);
		rawVertices.push_back(v.y);
	};

	
	// Convert attributes to vertex list
	for (int i = 0; i < vertices.size(); i++)
	{
		Vertex v = vertices[i];

		AddVec3(v.position);
		AddVec2(v.texCoord);
		AddVec3(v.colour);
		AddVec3(v.normal);
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
	GLuint attrib = 0;
	GLuint memorySize = 11 * sizeof(GLfloat);
	GLuint stride = 0;

	auto AddAttribute = [&](GLuint Size, GLenum Normalized = GL_FALSE)
	{
		glVertexAttribPointer(attrib, Size, GL_FLOAT, Normalized, memorySize, (void*)stride); // change me
		stride += Size * sizeof(GLfloat);
		glEnableVertexAttribArray(attrib);
		attrib++;
	};

	/*// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, memorySize, (void*)stride); // change me
	stride += 3 * sizeof(GLfloat);
	glEnableVertexAttribArray(0);

	// TexCoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, memorySize, (void*)stride); // change me
	stride += 2 * sizeof(GLfloat);
	glEnableVertexAttribArray(1);

	// Vertex Colour
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, memorySize, (void*)stride); // change me
	stride += 3 * sizeof(GLfloat);
	glEnableVertexAttribArray(2);*/

	AddAttribute(3); // Position
	AddAttribute(2); // TexCoord
	AddAttribute(3); // Colour
	AddAttribute(4, GL_TRUE); // Normal
}

void Primitive::Draw(const glm::mat4& Transform)
{
	ShaderProgram* shaderProgram = ShaderProgram::GetCurrent();
	if (shaderProgram != nullptr && shaderProgram->IsValid())
	{
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::toMat4(transform.rotation) * trans;
		trans = glm::translate(trans, transform.position);
		trans = glm::scale(trans, transform.scale);
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
	Draw(transform.GetMatrix());
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

void Primitive::SetColour(const glm::vec3 & Colour)
{
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].colour = Colour;
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