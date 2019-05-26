#include "Shader.h"



std::string Shader::GetSource(std::string File)
{
	std::ifstream inFile;
	inFile.open(File); // Try to open file
	std::string source; // String to dump to

	if (inFile.is_open()) // If open
	{
		std::stringstream strStream; // Stream to output to
		strStream << inFile.rdbuf(); // Output file contents to stream
		source = strStream.str();	 // Get string from stream
	}
	
	inFile.close();
	return source;
}

Shader::Shader()
{
}

Shader::Shader(const GLenum& ShaderType)
	: shaderType(ShaderType)
{
	// Shaders source
	std::string source = GetSource("Vertex.glsl");
}


Shader::~Shader()
{
}

GLint Shader::CompileSource(const std::string& Source)
{
	const GLchar* source_cstr = Source.c_str();
	ID = glCreateShader(shaderType);					// Create shader and return index
	glShaderSource(ID, 1, &source_cstr, NULL);		// Pass shader source
	glCompileShader(ID);								// Compile the shader

	GLchar infoLog[512];
	GLint success = GetLog(infoLog);

	if (success)
		std::cout << "Shader successfully compiled: " << GetShaderType() << std::endl;
	else
		std::cout << "Error: Shader failed to compile: " << GetShaderType() << "\n" << std::string(infoLog) << std::endl;

	return success;
}


GLint Shader::CompileFile(const std::string& File)
{
	std::string source = Shader::GetSource(File);
	return CompileSource(source);
}

GLint Shader::GetLog(GLchar* InfoLog)
{
#define LOG_SIZE 512

	GLint success;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

	if (!success)
		glGetShaderInfoLog(ID, LOG_SIZE, NULL, InfoLog);

	return success;
}

std::string Shader::GetShaderType()
{
	if (shaderType == GL_FRAGMENT_SHADER)
		return "FRAGMENT";
	else
		return "VERTEX";
}
