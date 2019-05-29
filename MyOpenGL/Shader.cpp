#include "Shader.h"

Shader* Shader::current = nullptr;

Shader::Shader()
{

}

Shader::Shader(const std::string & Folder)
{
	CompileShadersFromFolder(Folder);
}


Shader::~Shader()
{
}

GLint Shader::CompileShadersFromFolder(const std::string & Folder)
{
	GLint success = 1;
	
	// Shaders
	vertexShader = SubShader(GL_VERTEX_SHADER);
	success = vertexShader.CompileFile(Folder + "/Vertex.glsl") && success;
	fragmentShader = SubShader(GL_FRAGMENT_SHADER);
	success = fragmentShader.CompileFile(Folder + "/Fragment.glsl") && success;

	return success;
}

GLint Shader::LinkShaders()
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

void Shader::Bind()
{
	glUseProgram(ID);
	current = this;
}

void Shader::Unbind()
{
	glUseProgram(-1);
}

void Shader::SetBool(const GLchar* Name, const GLboolean& Value) const
{
	SetInt(Name, Value);
}

void Shader::SetInt(const GLchar* Name, const GLint& Value) const
{
	glUniform1i(GetUniformLocation(Name), Value);
}

void Shader::SetFloat(const GLchar * Name, const GLfloat& Value) const
{
	glUniform1f(GetUniformLocation(Name), Value);
}

void Shader::SetVec3(const GLchar * Name, const glm::vec3 & Value) const
{
	glUniform3f(GetUniformLocation(Name), Value.x, Value.y, Value.z);
}

void Shader::SetMatrix4x4(const GLchar * Name, const glm::mat4& Value) const
{
	glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, glm::value_ptr(Value));
}

void Shader::SetModelMatrix(const glm::mat4 & Model) const
{
	SetMatrix4x4(MODEL_MATRIX, Model);
}

void Shader::SetViewMatrix(const glm::mat4& View) const
{
	SetMatrix4x4(VIEW_MATRIX, View);
}

void Shader::SetProjectionMatrix(const glm::mat4& Projection) const
{
	SetMatrix4x4(PROJECTION_MATRIX, Projection);
}

void Shader::SetCameraPosition(const glm::vec3 & ViewPosition) const
{
	SetVec3("CameraPosition", ViewPosition);
}

void Shader::SetCameraDirection(const glm::vec3 & ViewDirection) const
{
	SetVec3("CameraDirection", ViewDirection);
}

GLint Shader::GetUniformLocation(const GLchar* Name) const
{
	if (IsValid())
		return glGetUniformLocation(ID, Name);
	else
		return -1;
}

Shader * Shader::GetCurrent()
{
	return current;
}
