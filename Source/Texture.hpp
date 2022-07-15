/*!*****************************************************************************
* \file Stub.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "glew.h"
#include <string>
#pragma once
namespace Orion
{
	/*!*************************************************************************
	* \class 
	* \brief 
	***************************************************************************/
	class Texture
	{
	public:
		//! Does nothing.
		Texture(std::string filename);
		//! Does nothing.
		GLuint GetID();
		//! Does nothing.
		std::string GetName();
		//! Does nothing.
		void SetName(std::string);
		//! Does nothing.
		void SetID();
	private:
		GLuint m_id{ 0 };
		std::string m_name;
	};
}