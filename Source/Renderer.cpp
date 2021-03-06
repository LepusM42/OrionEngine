/*!*****************************************************************************
* \file Renderer.cpp
* \author Lepus
* \brief Displays graphics.
*******************************************************************************/
#include "glew.h"
#include "Mesh.hpp"
#include "Renderer.hpp"
#include "Rigel.hpp"
#include "Shader.hpp"
#include <iostream>
namespace Orion
{
	Mesh m;
	Rigel::Matrix<float> Renderer::s_world(4);
	/*!*************************************************************************
	* \fn void Renderer::Init();
	* \brief Initialize the renderer.
	***************************************************************************/
	void Renderer::Init()
	{
		GLenum retval = glewInit();
		if (retval == GLEW_OK)
		{
			ShaderProgram s;
			s.Init();
			m.Init();
			m.SetShader(s);
		}
		else
		{
			std::cout << glewGetErrorString(retval) << std::endl;
		}
	}

	/*!*************************************************************************
	* \fn void Renderer::Update();
	* \brief Update the renderer.
	***************************************************************************/
	void Renderer::Update()
	{
		m.Update();
	}

	/*!*************************************************************************
	* \fn Rigel::Matrix<float> GetWorldMatrix();
	* \brief World conversion matrix.
	* \return A matrix used to convert world to screen coordinates.
	***************************************************************************/
	Rigel::Matrix<float>& Renderer::GetWorldMatrix()
	{
		return s_world;
	}
}