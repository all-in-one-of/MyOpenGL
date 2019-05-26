#include <glad/glad.h>  // Hardware-specific loader
#include <GLFW/glfw3.h> // Window & input handler
#include "stb_image.h"  // Image loading library


// Our classes
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Primitive.h"


//#include <filesystem>
//namespace FileSystem = std::filesystem;


const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;


// ===================================== EVENTS ============================================

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
{
	// Make sure viewport matches new window dimensions when resized
	glViewport(0, 0, Width, Height);
}


// ===================================== MAIN ============================================

int main()
{
	// GLFW initialize
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// GLFW create window
	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "MyOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1; // Error
	}
	glfwMakeContextCurrent(window); // Set context to our new window
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// ===================================== LOAD IN OPENGL CONTEXT ============================================

	// Initialize GLAD: load all function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Load address of OpenGL function pointers to handle OS-specifics
	{
		std::cout << "Failed to initialize GLAD" << std::endl; // Error
		return -1; // Return error code
	}

	glEnable(GL_DEPTH_TEST);


	// ===================================== SHADERS ============================================

	std::string shadersDir = "E:/Documents/PostUniversity/OpenGL/MyOpenGL/Shaders/Main";
	ShaderProgram shaderProgram;
	shaderProgram.CompileShadersFromFolder(shadersDir);
	shaderProgram.LinkShaders();


	// ===================================== TEXTURES ============================================

	Texture tex = Texture("E:/Documents/PostUniversity/OpenGL/MyOpenGL/Content/1024x1024 Texel Density Texture 1.png");
	Texture tex2;
	tex2.format = Texture::Format::RGBA;
	tex2.LoadResource("E:/Documents/PostUniversity/OpenGL/MyOpenGL/Content/houdini-763d999dfe.png");
	shaderProgram.Bind();
	shaderProgram.SetInt("tex", 0);
	shaderProgram.SetInt("tex2", 1);


	// ===================================== VAO & VBO ============================================
	
	Primitive prim;

	// Geometry
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f })); // Top right
	prim.AddVertex(Primitive::Vertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f })); // Bottom right
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f })); // Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f })); // Top left

	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f })); // Top right
	prim.AddVertex(Primitive::Vertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f })); // Bottom right
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f })); // Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f })); // Top left

	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f })); // Top right
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f })); // Top left

	prim.indices = {
		0, 1, 3, // first triangle
		1, 2, 3,  // second triangle

		4, 5, 7,
		5, 6, 7,
	};

	prim.Construct();
	prim.transform = glm::rotate(prim.transform, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	// ===================================== MAIN THREAD ============================================

	while( !glfwWindowShouldClose(window) ) // While window is open
	{
		// Input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Close window on escape press
			glfwSetWindowShouldClose(window, true);

		else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			std::cout << "MODE: LIT" << std::endl;
		}
		else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			glLineWidth(5.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			std::cout << "MODE: WIREFRAME" << std::endl;
		}
		else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			glPointSize(5.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			std::cout << "MODE: POINTS" << std::endl;
		}

		else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			std::cout << "SHADERS HOT RECOMPILE" << std::endl;
			shaderProgram.CompileShadersFromFolder(shadersDir);
			shaderProgram.LinkShaders();
			shaderProgram.Bind();
			shaderProgram.SetInt("tex", 0);
			shaderProgram.SetInt("tex2", 1);
		}

		// Clear screen with colour
		glClearColor(0.2f, 0.3f, 0.3f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen & depth buffers with bitwise operation on flags


		// Bind textures
		glActiveTexture(GL_TEXTURE0);
		tex.Bind();
		glActiveTexture(GL_TEXTURE1);
		tex2.Bind();
		//glBindTexture(GL_TEXTURE_2D, 1);
		//tex.Bind(); // Bind our texture
		//tex2.Bind();


		// Bind shader program
		shaderProgram.Bind();
		shaderProgram.SetFloat("ElapsedTime", glfwGetTime());


		// Create & bind transform matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0f));
		GLfloat aspect = (GLfloat)SRC_WIDTH / (GLfloat)SRC_HEIGHT;
		projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
		shaderProgram.SetMatrix4x4("View", view);
		shaderProgram.SetMatrix4x4("Projection", projection);


		prim.Draw();


		// Check events to call & swap buffers
		glfwSwapBuffers(window); // Swap the colour buffer and show to screen
		glfwPollEvents(); // Check if any events (i.e. inputs) have been triggered
	}



	// ===================================== CLEAN-UP ============================================

	prim.Destroy();

	glfwTerminate(); // Clean up GLFW context
	return 0; // Return success code
}