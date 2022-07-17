#include "GL4Texture.hh"
#include <iostream>

GL4Texture::GL4Texture(const Image& image, TextureFilter filter)
{
	m_Width = image.GetWidth();
	m_Height = image.GetHeight();

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image.IsValid())
	{
		GLenum channels;
		GLenum type;
		switch (image.GetChannels())
		{
		case 1:
			type = GL_R8;
			channels = GL_R;
			break;
		case 2:
			type = GL_RG8;
			channels = GL_RG;
			break;
		case 3:
			type = GL_RGB8;
			channels = GL_RGB;
			break;
		case 4:
		default:
			type = GL_RGBA8;
			channels = GL_RGBA;
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, type, image.GetWidth(), image.GetHeight(), 0, channels, GL_UNSIGNED_BYTE, image.GetBuffer());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		glDeleteTextures(1, &m_TextureID);
		return;
	}
}

GL4Texture::~GL4Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

void GL4Texture::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_TextureID);
}

uint32_t GL4Texture::GetWidth() const
{
	return m_Width;
}

uint32_t GL4Texture::GetHeight() const
{
	return m_Height;
}

GLint GL4Texture::GetNativeMagFilver(TextureFilter filter)
{
	switch (filter)
	{
	default:
	case TextureFilter::Linear:
		return GL_LINEAR;
	case TextureFilter::Nearest:
		return GL_NEAREST;
	}
}

GLint GL4Texture::GetNativeMinFilver(TextureFilter filter)
{
	switch (filter)
	{
	default:
	case TextureFilter::Linear:
		return GL_LINEAR_MIPMAP_LINEAR;
	case TextureFilter::Nearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	}
}
