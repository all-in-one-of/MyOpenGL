#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

class Object // Base class for all resources
{
protected:
	GLint index = -1;

public:
	Object();
	~Object();

	// Getters
	GLint GetIndex() const;
	GLboolean IsValid() const;
};

