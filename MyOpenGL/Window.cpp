#include "Window.h"

//Window* Window::current = nullptr;

void Window::Resized(GLFWwindow * Window, int Width, int Height)
{
	// Make sure viewport matches new window dimensions when resized
	glViewport(0, 0, Width, Height);
}

Window::Window()
{
}

Window::Window(const GLuint & Width, const GLuint & Height, const GLchar * WindowName)
{
	Create(Width, Height, WindowName);
}


Window::~Window()
{
}

GLint  Window::Create(const GLuint& Width, const GLuint& Height, const GLchar* WindowName)
{
	window = glfwCreateWindow(Width, Height, WindowName, NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1; // Error
	}
	glfwMakeContextCurrent(window); // Set context to our new window
	glfwSetFramebufferSizeCallback(window, Window::Resized);

	return 1; // Success
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window); // Swap the colour buffer and show to screen
}
