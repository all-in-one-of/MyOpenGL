#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{

}


ShaderProgram::~ShaderProgram()
{
}

GLint ShaderProgram::CompileShadersFromFolder(const std::string & Folder)
{
	GLint success = 1;
	
	// Shaders
	vertexShader = Shader(GL_VERTEX_SHADER);
	success = vertexShader.CompileFile(Folder + "/Vertex.glsl") && success;
	fragmentShader = Shader(GL_FRAGMENT_SHADER);
	success = fragmentShader.CompileFile(Folder + "/Fragment.glsl") && success;

	return success;
}

GLint ShaderProgram::LinkShaders()
{
	// Shader program
	index = glCreateProgram();
	glAttachShader(index, vertexShader.GetIndex());
	glAttachShader(index, fragmentShader.GetIndex());
	glLinkProgram(index); // Link our shaders to the shader program

	// Shader program debugging
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(index, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(index, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKER" << infoLog << std::endl;
	}
	else
		std::cout << "SHADERS LINKED SUCCESSFULLY" << std::endl;

	glDeleteShader(vertexShader.GetIndex());
	glDeleteShader(fragmentShader.GetIndex());

	return success;
}

void ShaderProgram::Bind()
{
	glUseProgram(index);
}

void ShaderProgram::Unbind()
{
	glUseProgram(-1);
}

GLint ShaderProgram::GetIndex()
{
	return index;
}