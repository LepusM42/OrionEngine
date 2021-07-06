/*!*****************************************************************************
* \file Renderer.hpp
* \author Lepus
* \brief Displays graphics.
*******************************************************************************/
#pragma once
#include "Rigel.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Renderer
	* \brief Renders visual data to a rear buffer, which is displayed after
	* being swapped with the front buffer.
	***************************************************************************/
	class Renderer
	{
	public:
		//! Initialize the renderer.
		static void Init();
		//! Update the renderer.
		static void Update();
		//! World conversion matrix.
		static Rigel::Matrix<float>& GetWorldMatrix();
	private:
		static Rigel::Matrix<float> s_world;
	};
}