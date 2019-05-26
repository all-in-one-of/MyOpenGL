#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "stb_image.h"

class Texture
{

public:
	enum Type : GLenum // Wrapper for texture types
	{
		Texture1D = GL_TEXTURE_1D,
		Texture1DArray = GL_TEXTURE_1D_ARRAY,
		Texture2D = GL_TEXTURE_2D,
		Texture2DArray = GL_TEXTURE_2D_ARRAY,
		Texture2DMultiSample = GL_TEXTURE_2D_MULTISAMPLE,
		Texture2DMultiSampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
		Texture3D = GL_TEXTURE_3D,
		TextureCube = GL_TEXTURE_CUBE_MAP,
		TextureCubeArray = GL_TEXTURE_CUBE_MAP_ARRAY,
		TextureRectangle = GL_TEXTURE_RECTANGLE
	};

	enum WrapMode : GLenum // Wrapper for wrap mode
	{
		ClampToEdge = GL_CLAMP_TO_EDGE,
		MirroredRepeat = GL_MIRRORED_REPEAT,
		Repeat = GL_REPEAT
	};

	enum Filter : GLenum // Wrapper for mag filter
	{
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR
	};

	enum Format : GLenum // Compression format
	{
		R = GL_RED,
		RGB = GL_RGB,
		RGBA = GL_RGBA
	};

protected:
	GLuint index = -1;
	void Generate();

private:
	// Properties
	Type type = Type::Texture2D;
	WrapMode wrapMode = WrapMode::Repeat;
	Filter filter = Filter::Linear;
	
	int width, height, numOfChannels = 0;
	std::string source;

	void Init();


public:
	
	// Properties
	GLboolean GenerateMipMaps = GL_TRUE;
	Format format = Format::RGB;


	// Constructors & destructors
	Texture();
	Texture(const GLchar* File);
	~Texture();


	// Methods
	void Bind();
	void Unbind();
	void SetType(const Type& TextureType);
	void SetWrapMode(const WrapMode& TextureWrapMode);
	void SetFilter(const Filter& TextureFilter);
	GLint LoadResource(const GLchar* File);


	// Getters
	GLint GetIndex() const;
	GLboolean IsValid() const;
	Type GetType() const;
	WrapMode GetWrapMode() const;
	Filter GetFilter() const;

};