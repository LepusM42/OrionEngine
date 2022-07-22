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
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/*!*************************************************************************
	* \class Window
	* \brief Application window used to display visual data.
	***************************************************************************/
	class Window
	{
	public:
		//! Create the window and GL Context.
		void Init();
		//! Update the current state of the window.
		void Update();
		//! Shut down the window and GL Context.
		void Shutdown();
	private:
		//! GLFW window and GL Context used for rendering.
		GLFWwindow* s_window;
		//! Create a window instance.
		void CreateWindow(int width, int height, const char* name);
		//! Destroy a window instance.
		void DestroyWindow();
	};
}