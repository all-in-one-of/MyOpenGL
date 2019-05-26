#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{

}

ShaderProgram::ShaderProgram(const std::string & Folder)
{
	CompileShadersFromFolder(Folder);
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
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader.GetID());
	glAttachShader(ID, fragmentShader.GetID());
	glLinkProgram(ID); // Link our shaders to the shader program

	// Shader program debugging
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error: Shaders failed to link" << infoLog << std::endl;
	}
	else
		std::cout << "Shaders successfully linked" << std::endl;

	glDeleteShader(vertexShader.GetID());
	glDeleteShader(fragmentShader.GetID());

	return success;
}

void ShaderProgram::Bind()
{
	glUseProgram(ID);
}

void ShaderProgram::Unbind()
{
	glUseProgram(-1);
}

void ShaderProgram::SetBool(const GLchar* Name, GLboolean Value) const
{
	SetInt(Name, Value);
}

void ShaderProgram::SetInt(const GLchar* Name, GLint Value) const
{
	glUniform1i(GetUniformLocation(Name), Value);
}

void ShaderProgram::SetFloat(const GLchar * Name, GLfloat Value) const
{
	glUniform1f(GetUniformLocation(Name), Value);
}

void ShaderProgram::SetFloat(const GLchar * Name, GLdouble Value) const
{
	glUniform1f(GetUniformLocation(Name), Value);
	//glUniform1d(GetUniformLocation(Name), Value);
}

GLint ShaderProgram::GetUniformLocation(const GLchar* Name) const
{
	if (IsValid())
		return glGetUniformLocation(ID, Name);
	else
		return -1;
}