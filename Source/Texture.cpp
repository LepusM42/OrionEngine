/*!*****************************************************************************
* \file Stub.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Texture.hpp"
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
		glBindTexture(GL_TEXTURE_2D, m_id);
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