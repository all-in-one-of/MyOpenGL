#include "Texture2D.h"



Texture2D::Texture2D()
{
	Texture::Texture();
}

Texture2D::Texture2D(const GLchar * File)
{
	Texture::Texture(File);
}


Texture2D::~Texture2D()
{
	Texture::~Texture();
}
