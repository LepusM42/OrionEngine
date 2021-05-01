/******************************************************************************!
* \file Window.cpp
* \author Lepus
* \brief Creates and manages the application window.
*******************************************************************************/
#include "Window.hpp"
#include "Engine.hpp"
namespace Orion
{
	GLFWwindow* Window::s_window;
	/**************************************************************************!
	* \fn Window::Init(int, int, const char*);
	* \brief Create the window and GL Context.
	***************************************************************************/
	void Window::Init()
	{
		if (glfwInit() == GLFW_TRUE)
		{
			CreateWindow(800, 600, "Golem Farm");
			glfwSetWindowCloseCallback(s_window, WindowCloseCallback);
		}
		else
		{

		}
	}
	/**************************************************************************!
	* \fn void Window::Update();
	* \brief Update the current state of the window.
	***************************************************************************/
	void Window::Update()
	{
		if (!glfwWindowShouldClose(s_window))
		{
			glfwSwapBuffers(s_window);
			glfwPollEvents();
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

	/**************************************************************************!
	* \fn Window::CreateWindow(int width, int height, const char* name);
	* \brief Create a window instance.
	* \param width Width of the window, in pixels.
	* \param height Height of the window, in pixels.
	* \param name Name to be displayed on the top of the application window.
	***************************************************************************/
	void Window::CreateWindow(int width, int height, const char* name)
	{
		if (!s_window)
		{
			s_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		}
	}
	/**************************************************************************!
	* \fn CreateWindow(int width, int height, const char* name);
	* \brief Callback used when the window is closed.
	* \param window Window that was closed.
	***************************************************************************/
	void WindowCloseCallback(GLFWwindow*)
	{
		Engine::NotifyShutdown();
	}
}