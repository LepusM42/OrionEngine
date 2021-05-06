/******************************************************************************!
* \file Renderer.hpp
* \author Lepus
* \brief Displays graphics.
*******************************************************************************/
#pragma once
namespace Orion
{
	/**************************************************************************!
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
	private:
	};
}