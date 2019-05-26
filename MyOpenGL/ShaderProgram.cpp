#include "ShaderProgram.h"

ShaderProgram* ShaderProgram::current = nullptr;

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
	current = this;
}

void ShaderProgram::Unbind()
{
	glUseProgram(-1);
}

void ShaderProgram::SetBool(const GLchar* Name, const GLboolean& Value) const
{
	SetInt(Name, Value);
}

void ShaderProgram::SetInt(const GLchar* Name, const GLint& Value) const
{
	glUniform1i(GetUniformLocation(Name), Value);
}

void ShaderProgram::SetFloat(const GLchar * Name, const GLfloat& Value) const
{
	glUniform1f(GetUniformLocation(Name), Value);
}

void ShaderProgram::SetMatrix4x4(const GLchar * Name, const glm::mat4& Value) const
{
	glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, glm::value_ptr(Value));
}

void ShaderProgram::SetModelMatrix(const glm::mat4 & Model) const
{
	SetMatrix4x4(MODEL_MATRIX, Model);
}

void ShaderProgram::SetViewMatrix(const glm::mat4& View) const
{
	SetMatrix4x4(VIEW_MATRIX, View);
}

void ShaderProgram::SetProjectionMatrix(const glm::mat4& Projection) const
{
	SetMatrix4x4(PROJECTION_MATRIX, Projection);
}

GLint ShaderProgram::GetUniformLocation(const GLchar* Name) const
{
	if (IsValid())
		return glGetUniformLocation(ID, Name);
	else
		return -1;
}

ShaderProgram * ShaderProgram::GetCurrent()
{
	return current;
}
