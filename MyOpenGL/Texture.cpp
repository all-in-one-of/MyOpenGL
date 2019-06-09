#include "Texture.h"

Texture* Texture::current = nullptr;

void Texture::Generate() // Add to our texture pool
{
	GLuint cachedID;
	glGenTextures(1, &cachedID);
	ID = cachedID;

	SetType(type);

	std::cout << "Generated texture object: " << ID << std::endl;
}

void Texture::Init()
{
	Generate(); // Generate the texture so we can bind the ID
	Bind(); // First bind so we can set the properties

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
	{
		if (current != this)
		{
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(type, ID);
			current = this;
		}
	}
	else
		std::cout << "Error: Failed to bind texture object: `" << source << std::endl;
}

void Texture::Unbind()
{
	/*Bind();
	glDisable(type);*/

	ID = -1;
}

void Texture::SetType(const Texture::Type & TextureType)
{
	type = TextureType;
}

void Texture::SetWrapMode(const Texture::WrapMode & TextureWrapMode)
{
	Bind();
	wrapMode = TextureWrapMode;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
}

void Texture::SetFilter(const Texture::Filter & TextureFilter)
{
	Bind();
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
		stbi_set_flip_vertically_on_load(FlipVertical); // Fix flipping
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
		std::cout << "ERROR: Texture object invalid: '" << File << "'\n";

	return success;
}

GLboolean Texture::IsValid() const
{
	return ID >= 1;
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

GLint Texture::GetWidth() const
{
	return width;
}

GLint Texture::GetHeight() const
{
	return height;
}

GLint Texture::GetNumberOfChannels() const
{
	return numOfChannels;
}