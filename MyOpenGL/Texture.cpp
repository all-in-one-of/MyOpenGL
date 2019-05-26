#include "Texture.h"


void Texture::Generate()
{
	GLuint cachedIndex;
	glGenTextures(1, &cachedIndex);
	index = cachedIndex;

	std::cout << "Generated texture object: " << index << std::endl;
}

void Texture::Init()
{
	Generate(); // Generate the index

	Bind(); // First bind so we can set the properties

	SetType(type);
	SetWrapMode(wrapMode);
	SetFilter(filter);
}


Texture::Texture()
{
	Init();
}

Texture::Texture(const GLchar * File)
{
	Init();
	LoadResource(File);
}


Texture::~Texture()
{
}

void Texture::Bind()
{
	if (IsValid())
		glBindTexture(type, index);
}

void Texture::Unbind()
{
	index = -1;
}

void Texture::SetType(const Texture::Type & TextureType)
{
	type = TextureType;
}

void Texture::SetWrapMode(const Texture::WrapMode & TextureWrapMode)
{
	wrapMode = TextureWrapMode;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
}

void Texture::SetFilter(const Texture::Filter & TextureFilter)
{
	filter = TextureFilter;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}


GLint Texture::LoadResource(const GLchar* File)
{
	GLint success = -1; // Default to fail
	source = File;

	if (IsValid()) // If we have valid texture memory allocated first
	{
		unsigned char* data = stbi_load(File, &width, &height, &numOfChannels, 0);

		if (data) // If the data is valid
		{
			glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

			if (GenerateMipMaps)
				glGenerateMipmap(type);

			std::cout << "Texture successfully loaded: '" << File << "'\n";

			success = 1;
		}
		else
			std::cout << "ERROR: Failed to load texture: '" << File << "'\n";

		stbi_image_free(data); // Free up memory
	}
	else
	{
		std::cout << "ERROR: Texture object invalid: '" << File << "'\n";
	}

	return success;
}

Texture::Type Texture::GetType() const
{
	return type;
}

Texture::WrapMode Texture::GetWrapMode() const
{
	return wrapMode;
}

Texture::Filter Texture::GetFilter() const
{
	return filter;
}
