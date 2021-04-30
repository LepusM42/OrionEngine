/******************************************************************************!
* \file Window.hpp
* \author Lepus
* \brief Creates and manages the application window.
*******************************************************************************/
#pragma once
#include "glfw3.h"
namespace Orion
{
	/**************************************************************************!
	* \class Foo
	* \brief Template for a class.
	***************************************************************************/
	class Window
	{
	public:
		//!< Create the window and GL Context.
		static void Init(int width, int height, const char* name);
		//!< Shut down the window and GL Context.
		static void Shutdown();
	private:
		static GLFWwindow* s_window;
	};
}