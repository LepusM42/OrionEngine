/******************************************************************************!
* \file Window.cpp
* \author Lepus
* \brief Creates and manages the application window.
*******************************************************************************/
#include "Window.hpp"
namespace Orion
{
	GLFWwindow* Window::s_window;
	/**************************************************************************!
	* \fn Window::Init(int, int, const char*);
	* \brief Window constructor.
	* \param w Width of the window, in pixels.
	* \param h Height of the window, in pixels.
	* \param name Name to be displayed on the top of the application window.
	***************************************************************************/
	void Window::Init(int w, int h, const char* name)
	{
		if (glfwInit() == GLFW_TRUE)
		{
			if (!s_window)
			{
				s_window = glfwCreateWindow(w, h, name, nullptr, nullptr);
			}
		}
		else
		{

		}
	}
	/**************************************************************************!
	* \fn Window::Shutdown();
	* \brief Shut down the window and GL Context.
	***************************************************************************/
	void Window::Shutdown()
	{
		glfwTerminate();
	}
}