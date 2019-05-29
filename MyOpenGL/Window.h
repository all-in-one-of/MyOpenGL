#pragma once

#include <glad/glad.h>  // Hardware-specific loader
#include <GLFW/glfw3.h> // Window & input handler

// GLM Mathematics library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Window
{
private:
	static void Resized(GLFWwindow* Window, int Width, int Height);
	static Window* current;

public:
	// Properties
	GLFWwindow* window;

	Window();
	Window(const GLuint& Width, const GLuint& Height, const GLchar* WindowName = "NewWindow");
	~Window();

	// Methods
	GLint Create(const GLuint& Width, const GLuint& Height, const GLchar* WindowName = "NewWindow");
	void SwapBuffers();
	void Bind();

	
	// Getters
	glm::ivec2 GetSize() const;
	static GLFWwindow* GetCurrent();
	static Window* GetCurrentObject();
};

