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
	index = glCreateShader(shaderType);					// Create shader and return index
	glShaderSource(index, 1, &source_cstr, NULL);		// Pass shader source
	glCompileShader(index);								// Compile the shader

	GLchar infoLog[512];
	GLint success = GetLog(infoLog);

	if (success)
		std::cout << "COMPILED SHADER SUCCESSFULLY" << std::endl;
	else
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << std::string(infoLog) << std::endl;

	return success;
}


GLint Shader::CompileFile(const std::string& File)
{
	std::string source = Shader::GetSource(File);
	return CompileSource(source);
}


GLint Shader::GetIndex()
{
	return index;
}



GLint Shader::GetLog(GLchar* InfoLog)
{
#define LOG_SIZE 512

	GLint success;
	glGetShaderiv(index, GL_COMPILE_STATUS, &success);

	if (!success)
		glGetShaderInfoLog(index, LOG_SIZE, NULL, InfoLog);

	return success;
}