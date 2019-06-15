#include <glad/glad.h>  // Hardware-specific loader
#include <GLFW/glfw3.h> // Window & input handler
#include "stb_image.h"  // Image loading library


// Our classes
#include "Window.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Mesh.h"
#include "EditorCamera.h"


const GLuint SRC_WIDTH = 1280;
const GLuint SRC_HEIGHT = 720;
Window window;
EditorCamera camera;
Shader shaderProgram, unlitShader, cubemapShader;

double elapsedTime = 0.0f, deltaTime = 0.0f;

// ===================================== EVENTS ============================================

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.UpdateFOV(deltaTime, glm::vec2(xoffset, yoffset));
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	camera.UpdateMouse(deltaTime, glm::vec2(xpos, ypos));
}

void EditorInput(const float& DeltaTime)
{
	// Input
	if (glfwGetKey(Window::GetCurrent(), GLFW_KEY_ESCAPE) == GLFW_PRESS) // Close window on escape press
		glfwSetWindowShouldClose(Window::GetCurrent(), true);

	else if (glfwGetKey(Window::GetCurrent(), GLFW_KEY_1) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		std::cout << "MODE: LIT" << std::endl;
	}
	else if (glfwGetKey(Window::GetCurrent(), GLFW_KEY_2) == GLFW_PRESS)
	{
		glLineWidth(5.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		std::cout << "MODE: WIREFRAME" << std::endl;
	}
	else if (glfwGetKey(Window::GetCurrent(), GLFW_KEY_3) == GLFW_PRESS)
	{
		glPointSize(5.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		std::cout << "MODE: POINTS" << std::endl;
	}
	else if (glfwGetKey(Window::GetCurrent(), GLFW_KEY_R) == GLFW_PRESS) // HOT RECOMPILE
	{
		std::cout << "SHADERS HOT RECOMPILE" << std::endl;
		Shader::RecompileAll();
	}
}

// ===================================== MAIN ============================================

int main(int argc, char* argv[])
{
	// GLFW initialize
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// GLFW create window
	window = Window(SRC_WIDTH, SRC_HEIGHT, "MyOpenGL");
	glfwSetScrollCallback(window.window, ScrollCallback);
	glfwSetCursorPosCallback(window.window, MouseCallback);
	glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Capture cursor input but always reset cursor to screen centre


	// ===================================== LOAD IN OPENGL CONTEXT ============================================

	// Initialize GLAD: load all function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Load address of OpenGL function pointers to handle OS-specifics
	{
		std::cout << "Failed to initialize GLAD" << std::endl; // Error
		return -1; // Return error code
	}

	glEnable(GL_DEPTH_TEST);

	// ===================================== CAMERA ============================================

	camera.fieldOfView = 65.0f;
	camera.transform.position = glm::vec3(0.0f, 0.0f, 3.0f);
	camera.cursorPosition = glm::vec2((GLfloat)window.GetSize().x / 2.0f, (GLfloat)window.GetSize().y / 2.0f);
	//camera.transform.rotation = glm::quat(glm::vec3(0.0f, glm::radians(180.0f), 0.0));


	// ===================================== TEXTURES ============================================

	Texture tex = Texture("../Content/1024x1024 Texel Density Texture 1.png");
	Texture tex2;
	tex2.SetFormat(Texture::Format::RGBA);
	tex2.LoadResource("../Content/houdini-763d999dfe.png");

	Texture environmentMap;
	environmentMap.SetFormatHDR();
	environmentMap.SetWrapMode(Texture::WrapMode::ClampToEdge);
	environmentMap.LoadResource("../Content/small_hangar_01_1k.hdr");

	// ===================================== SHADERS & MATERIALS ============================================

	shaderProgram.Compile("../Shaders/Main");
	unlitShader.Compile("../Shaders/Unlit");
	cubemapShader.Compile("../Shaders/Cubemap");


	Material unlitMaterial(&unlitShader);
	unlitMaterial.name = "Unlit_MI";

	Material cubemapMaterial(&cubemapShader);
	cubemapMaterial.name = "Cubemap_MI";
	cubemapMaterial.SetTextureParameter("EquirectangularMap", &environmentMap);

	Material checkerMaterial(&shaderProgram);
	checkerMaterial.name = "Checker_MI";
	checkerMaterial.SetTextureParameter("tex", &tex);
	checkerMaterial.SetTextureParameter("tex2", &environmentMap);
	checkerMaterial.SetVectorParameter("inMaterial.Albedo", glm::vec3(1.0f));
	checkerMaterial.SetFloatParameter("inMaterial.Metalness", 0.0f);
	checkerMaterial.SetFloatParameter("inMaterial.Roughness", 0.25f);
	checkerMaterial.SetFloatParameter("inMaterial.AmbientOcclusion", 1.0f);

	Material sphereMaterial(&shaderProgram);
	sphereMaterial.name = "Sphere_MI";
	sphereMaterial.SetTextureParameter("tex", &tex);
	sphereMaterial.SetTextureParameter("tex2", &tex2);
	sphereMaterial.SetVectorParameter("inMaterial.Albedo", glm::vec3(1.0f, 0.1f, 0.7f));
	sphereMaterial.SetFloatParameter("inMaterial.Metalness", 1.0f);
	sphereMaterial.SetFloatParameter("inMaterial.Roughness", 0.25f);
	sphereMaterial.SetFloatParameter("inMaterial.AmbientOcclusion", 1.0f);


	// ===================================== VAO & VBO ============================================
	
	Mesh box;
	//box.LoadMeshObj("../Content/Box_SM.obj");
	box.transform.rotation = glm::quat(glm::radians(glm::vec3(0.0f, 45.0f, 0.0f)));
	box.transform.position = glm::vec3(-5.0f, 0.0f, 0.0f);
	box.material = &unlitMaterial;

	Mesh sphere;
	sphere.LoadMeshObj("../Content/Sphere_SM.obj");
	sphere.material = &sphereMaterial;
	sphere.transform.position = glm::vec3(-2.0f, -.3f, 1.0f);


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
	plane.transform.scale = glm::vec3(3.0f);
	plane.transform.position = glm::vec3(0.0f, -.35f, 0.0f);
	plane.material = &unlitMaterial;


	Primitive prim;
	prim.material = &cubemapMaterial;

	// Geometry
	// Front face
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f })); // Front - Top right
	prim.AddVertex(Primitive::Vertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f })); // Front - Bottom right
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f })); // Front - Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f })); // Front - Top left

	// Back face
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f })); // Back  - Top right
	prim.AddVertex(Primitive::Vertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f })); // Back  - Bottom right
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f })); // Back  - Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f })); // Back -  Top left

	// Top face
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f })); // Front - Top right
	prim.AddVertex(Primitive::Vertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })); // Back  - Top right
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })); // Back  - Top left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f })); // Front - Top left

	// Bottom face
	prim.AddVertex(Primitive::Vertex({ 0.5f,   -0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f })); // Front - Top right
	prim.AddVertex(Primitive::Vertex({ 0.5f,   -0.5f, -0.5f }, { 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f })); // Back  - Top right
	prim.AddVertex(Primitive::Vertex({ -0.5f,  -0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f })); // Back  - Top left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  -0.5f,  0.5f }, { 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f })); // Front - Top left

	// Left face
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f })); // Front - Top left
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f })); // Front - Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f })); // Back  - Bottom left
	prim.AddVertex(Primitive::Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f })); // Back -  Top left

	// Right face
	prim.AddVertex(Primitive::Vertex({ 0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f })); // Front - Top left
	prim.AddVertex(Primitive::Vertex({ 0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })); // Front - Bottom left
	prim.AddVertex(Primitive::Vertex({ 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })); // Back  - Bottom left
	prim.AddVertex(Primitive::Vertex({ 0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f })); // Back -  Top left

	prim.SetColour(glm::vec3(0.0f, 1.0f, 0.0f));
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


	// ===================================== MAIN THREAD ============================================

	window.Bind();
	camera.Bind();

	while( !glfwWindowShouldClose(Window::GetCurrent()) ) // While window is open
	{
		// Delta & elapsed time
		double time = glfwGetTime();
		deltaTime = time - elapsedTime;
		elapsedTime = time;


		// Camera controls
		camera.Update(deltaTime);


		if (glfwGetKey(Window::GetCurrent(), GLFW_KEY_0) == GLFW_PRESS)
			box.transform.position += Transform::WORLD_RIGHT * (float)deltaTime * 1.5f;
		else if (glfwGetKey(Window::GetCurrent(), GLFW_KEY_9) == GLFW_PRESS)
			box.transform.position -= Transform::WORLD_RIGHT * (float)deltaTime * 1.5f;


		EditorInput(deltaTime);


		// Clear screen with colour
		glClearColor(0.2f, 0.3f, 0.3f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen & depth buffers with bitwise operation on flags


		// Bind textures
		/*glActiveTexture(GL_TEXTURE0);
		tex.Bind();
		glActiveTexture(GL_TEXTURE1);
		tex2.Bind();*/

		//glBindTexture(GL_TEXTURE_2D, 1);
		//tex.Bind(); // Bind our texture
		//tex2.Bind();


		// Bind shader program
		//shaderProgram.Bind();
		//shaderProgram.SetFloat("ElapsedTime", elapsedTime); // Move me into shader callback
		//camera.Draw();

		//Draw meshes
		box.Draw();
		sphere.Draw();
		plane.Draw();
		prim.Draw();

		for (int i = 0; i < positions.size(); i++)
		{
			glm::mat4 transform = glm::mat4(1.0f); // Identity
			transform = glm::translate(transform, positions[i]);
			prim.Draw(prim.transform.GetMatrix() * transform);
		}


		// Check events to call & swap buffers
		window.SwapBuffers();

		// Safely unbind last shader
		Shader::Unbind();

		glfwPollEvents(); // Check if any events (i.e. inputs) have been triggered
	}



	// ===================================== CLEAN-UP ============================================

	box.Destroy();
	prim.Destroy();
	plane.Destroy();

	Shader::Cleanup();
	Primitive::Cleanup();
	glfwTerminate(); // Clean up GLFW context
	return 0; // Return success code
}