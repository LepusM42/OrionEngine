/*!*****************************************************************************
* \file Window.hpp
* \author Lepus
* \brief Creates and manages the application window.
*******************************************************************************/
#pragma once
#include "glfw3.h"
namespace Orion
{
	//! Global callback used when a window is closed.
	void WindowCloseCallback(GLFWwindow* window);

	/*!*************************************************************************
	* \class Window
	* \brief Application window used to display visual data.
	***************************************************************************/
	class Window
	{
	public:
		//! Create the window and GL Context.
		static void Init();
		//! Update the current state of the window.
		static void Update();
		//! Shut down the window and GL Context.
		static void Shutdown();
	private:
		//! GLFW window and GL Context used for rendering.
		static GLFWwindow* s_window;
		//! Create a window instance.
		static void CreateWindow(int width, int height, const char* name);
	};
}