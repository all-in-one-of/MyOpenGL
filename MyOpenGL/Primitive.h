#pragma once

#include "Transform.h"
#include "Object.h"
#include "Material.h"

#include <vector>


class Primitive : public Object
{
public:
	class Vertex // Container for vertex attributes. Position is only one attribute, not the location of the "vertex" itself.
	{
	public:
		// Properties
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec2 texCoord = glm::vec3(0.0f);
		glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);


		Vertex() {};
		Vertex(const glm::vec3& Position)
			: position(Position) {};
		Vertex(const glm::vec3& Position, const glm::vec2& TexCoord)
			: position(Position), texCoord(TexCoord) {};
		Vertex(const glm::vec3& Position, const glm::vec2& TexCoord, const glm::vec3& Normal)
			: position(Position), texCoord(TexCoord), normal(Normal) {};
		~Vertex() {};
	};


private:
	GLuint VBO, VAO, EBO;

protected:
	std::vector<GLfloat> GetRawVertices() const;
	glm::vec3 minBounds, maxBounds;

public:
	// Properties
	Transform transform;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Material* material; // We will change this to be stored in mesh sections
	enum DrawMode : GLuint
	{
		DrawElements = 0,
		DrawArrays = 1
	} drawMode = DrawMode::DrawElements;


	// Constructors & destructors
	Primitive();
	~Primitive();


	// Methods
	void Construct();
	void Draw(const glm::mat4& Transform);
	void Draw();
	void Destroy();
	void WeldAllVertices();
	void WeldVertices(const std::vector<int>& Indices);
	void RemoveIsolatedVertices();
	//void CalculateBounds(); // IMPLMENT ME


	// Setters
	void AddVertex(const Vertex& NewVertex);
	void SetColour(const glm::vec3& Colour);


	// Getters
	GLuint GetVBO() const;
	GLuint GetVAO() const;
	GLuint GetEBO() const;
};

