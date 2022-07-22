/*!*****************************************************************************
* \file Stub.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Orion
{
	/*!*************************************************************************
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Texture::Texture(std::string filename)
	{
		SetID();
		int width, height, channels;
		image = stbi_load(filename.c_str(), &width, &height, &channels, 3);
		stbi__vertical_flip(image, width, height, 3);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 10);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)GL_LINEAR_MIPMAP_LINEAR);

		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(image);
	}

	/*!*************************************************************************
	* \fn 
	* \brief 
	* \param 
	* \return 
	***************************************************************************/
	GLuint Texture::GetID()
	{
		return m_id;
	}

	/*!*************************************************************************
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	std::string Texture::GetName()
	{
		return m_name;
	}

	/*!*************************************************************************
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Texture::SetName(std::string name)
	{
		m_name = name;
	}

	/*!*************************************************************************
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Texture::SetID()
	{
		glGenTextures(1, &m_id);
	}
}