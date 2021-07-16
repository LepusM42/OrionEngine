/*!*****************************************************************************
* \file Stub.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include "glew.h"
#include "Shader.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Foo
	* \brief Template for a class.
	***************************************************************************/
	class Mesh
	{
	public:
		void Init();
		void Update();
		GLuint GetVArray();
		GLuint GetVBuffer();
		GLuint GetIBuffer();
		~Mesh();
	private:
		GLuint m_VAO{ 0 };      //!< Vertex array object holding vertices.
		GLuint m_VBO{ 0 };      //!< Buffer object holding raw vertex data.
		GLuint m_IBO{ 0 };		//!< Buffer holding a list of vertex indices.
		float m_scale{ 1.0f };
	};
}