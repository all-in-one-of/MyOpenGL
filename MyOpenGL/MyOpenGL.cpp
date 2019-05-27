#include <glad/glad.h>  // Hardware-specific loader
#include <GLFW/glfw3.h> // Window & input handler
#include "stb_image.h"  // Image loading library


// Our classes
#include "Window.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Primitive.h"
#include "EditorCamera.h"


//#include <filesystem>
//namespace FileSystem = std::filesystem;


const GLuint SRC_WIDTH = 800;
const GLuint SRC_HEIGHT = 600;
Window window;

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
	window = Window(SRC_WIDTH, SRC_HEIGHT, "MyOpenGL");

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
	
	Primitive plane;

	plane.AddVertex(Primitive::Vertex({  0.5f,  0.0f, -0.5f }, { 1.0f, 1.0f })); // Front - Top right
	plane.AddVertex(Primitive::Vertex({  0.5f, -0.0f,  0.5f }, { 1.0f, 0.0f })); // Front - Bottom right
	plane.AddVertex(Primitive::Vertex({ -0.5f, -0.0f,  0.5f }, { 0.0f, 0.0f })); // Front - Bottom left
	plane.AddVertex(Primitive::Vertex({ -0.5f,  0.0f, -0.5f }, { 0.0f, 1.0f })); // Front - Top left
	plane.indices = {
		0, 1, 3,
		1, 2, 3
	};
	plane.Construct();
	//plane.transform.scale = glm::vec3(3.0f);
	//plane.transform.position = glm::vec3(0.0f, -.35f, 0.0f);
	



	Primitive prim;

	// Geometry
	// Front face
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f })); // Front - Top right
	prim.AddVertex(Primitive::Vertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f })); // Front - Bottom right
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f })); // Front - Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f })); // Front - Top left

	// Back face
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f })); // Back  - Top right
	prim.AddVertex(Primitive::Vertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f })); // Back  - Bottom right
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f })); // Back  - Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f })); // Back -  Top left

	// Top face
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f })); // Front - Top right
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f })); // Back  - Top right
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f })); // Back  - Top left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f })); // Front - Top left

	// Bottom face
	prim.AddVertex(Primitive::Vertex({ 0.5f,   -0.5f,  0.5f }, { 1.0f, 1.0f })); // Front - Top right
	prim.AddVertex(Primitive::Vertex({ 0.5f,   -0.5f, -0.5f }, { 1.0f, 0.0f })); // Back  - Top right
	prim.AddVertex(Primitive::Vertex({ -0.5f,  -0.5f, -0.5f }, { 0.0f, 0.0f })); // Back  - Top left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  -0.5f,  0.5f }, { 0.0f, 1.0f })); // Front - Top left

	// Left face
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f })); // Front - Top left
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f })); // Front - Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f })); // Back  - Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f })); // Back -  Top left

	// Right face
	prim.AddVertex(Primitive::Vertex({ 0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f })); // Front - Top left
	prim.AddVertex(Primitive::Vertex({ 0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f })); // Front - Bottom left
	prim.AddVertex(Primitive::Vertex({ 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f })); // Back  - Bottom left
	prim.AddVertex(Primitive::Vertex({ 0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f })); // Back -  Top left

	prim.indices = {
		0, 1, 3, // first triangle
		1, 2, 3,  // second triangle

		4, 5, 7,
		5, 6, 7,

		8, 9, 11,
		9, 10, 11,

		12, 13, 15,
		13, 14, 15,

		16, 17, 19,
		17, 18, 19,

		20, 21, 23,
		21, 22, 23
	};

	prim.Construct();
	std::vector<glm::vec3> positions = { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, -1.0f, -.5f), glm::vec3(-2.0f, 1.5f, -2.0f) };

	// ===================================== CAMERA ============================================

	Camera camera;
	camera.SetAspect(SRC_WIDTH, SRC_HEIGHT);
	camera.fieldOfView = 45.0f;
	//camera.transform = glm::translate(camera.transform, glm::vec3(0.0f, 0.0f, -3.0f));
	camera.transform.position = glm::vec3(0.0f, 0.0f, 3.0f);



	// ===================================== MAIN THREAD ============================================

	double elapsedTime = 0.0f, deltaTime = 0.0f;

	while( !glfwWindowShouldClose(window.window) ) // While window is open
	{
		// Delta & elapsed time
		float time = glfwGetTime();
		deltaTime = time - elapsedTime;
		elapsedTime = time;


		// Camera controls
		float camSpeed = 1.5f;
		camSpeed = glfwGetKey(window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? camSpeed * 2.5f : camSpeed;
		//std::cout << glm::to_string(camera.transform.position) << std::endl;

		if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS)
			camera.transform.position += camera.transform.GetForward() * (float)deltaTime * camSpeed;
		else if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)
			camera.transform.position -= camera.transform.GetForward() * (float)deltaTime * camSpeed;
		if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
			camera.transform.position -= camera.transform.GetRight() * (float)deltaTime * camSpeed;
		else if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
			camera.transform.position += camera.transform.GetRight() * (float)deltaTime * camSpeed;
		if (glfwGetKey(window.window, GLFW_KEY_Q) == GLFW_PRESS)
			camera.transform.position += camera.transform.GetUp() * (float)deltaTime * camSpeed;
		else if (glfwGetKey(window.window, GLFW_KEY_E) == GLFW_PRESS)
			camera.transform.position -= camera.transform.GetUp() * (float)deltaTime * camSpeed;


		// Input
		if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Close window on escape press
			glfwSetWindowShouldClose(window.window, true);

		else if (glfwGetKey(window.window, GLFW_KEY_1) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			std::cout << "MODE: LIT" << std::endl;
		}
		else if (glfwGetKey(window.window, GLFW_KEY_2) == GLFW_PRESS)
		{
			glLineWidth(5.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			std::cout << "MODE: WIREFRAME" << std::endl;
		}
		else if (glfwGetKey(window.window, GLFW_KEY_3) == GLFW_PRESS)
		{
			glPointSize(5.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			std::cout << "MODE: POINTS" << std::endl;
		}
		else if (glfwGetKey(window.window, GLFW_KEY_R) == GLFW_PRESS) // HOT RECOMPILE
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
		shaderProgram.SetFloat("ElapsedTime", elapsedTime);

		camera.Bind();


		//Draw meshes
		plane.Draw();
		//prim.transform = glm::rotate(prim.transform, glm::radians((float)deltaTime * 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//prim.transform.rotation *= glm::quat(0.0f, 1.0f, 0.0f, cos((float)deltaTime * 30.0f));
		prim.Draw();
		for (int i = 0; i < positions.size(); i++)
		{
			glm::mat4 transform = glm::mat4(1.0f); // Identity
			transform = glm::translate(transform, positions[i]);
			prim.Draw(prim.transform.GetMatrix() * transform);
		}


		// Check events to call & swap buffers
		window.SwapBuffers();
		glfwPollEvents(); // Check if any events (i.e. inputs) have been triggered
	}



	// ===================================== CLEAN-UP ============================================

	prim.Destroy();

	glfwTerminate(); // Clean up GLFW context
	return 0; // Return success code
}