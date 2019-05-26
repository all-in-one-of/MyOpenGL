#include "Texture2D.h"



Texture2D::Texture2D()
{
	Texture::Init();
}

Texture2D::Texture2D(const GLchar * File)
{
	Texture::Init();
	Texture::LoadResource(File);
}

Texture2D::~Texture2D()
{
	Texture::~Texture();
}
