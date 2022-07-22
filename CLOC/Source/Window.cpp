/*!*****************************************************************************
* \file Window.cpp
* \author Lepus
* \brief Creates and manages the application window.
*******************************************************************************/
#include "glew.h"
#include "Window.hpp"
#include "Engine.hpp"
#include "Rigel.hpp"
#include "Input.hpp"
#include <iostream>
namespace Orion
{
	/*!*************************************************************************
	* \fn KeyCallback(GLFWwindow*, int, int, int, int)
	* \brief
	***************************************************************************/
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Input::SendEvent(key, action);
	}

	/*!*************************************************************************
	* \fn Window::Init(int, int, const char*);
	* \brief Create the window and GL Context.
	***************************************************************************/
	void Window::Init()
	{
		if (glfwInit() == GLFW_TRUE)
		{
			glfwWindowHint(GLFW_DOUBLEBUFFER, true);
			glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
			CreateWindow(800, 600, "OrionEngine");
			glfwMakeContextCurrent(s_window);
			glfwSetWindowCloseCallback(s_window, WindowCloseCallback);
			glfwSetKeyCallback(s_window, KeyCallback);
		}
		else
		{

		}
	}
	/*!*************************************************************************
	* \fn void Window::Update();
	* \brief Update the current state of the window.
	***************************************************************************/
	void Window::Update()
	{
		if (!glfwWindowShouldClose(s_window))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			GLbitfield mask = 0;
			mask |= GL_COLOR_BUFFER_BIT;
			mask |= GL_DEPTH_BUFFER_BIT;
			mask |= GL_STENCIL_BUFFER_BIT;
			glfwSwapBuffers(s_window);
			glClear(mask);
			glfwPollEvents();
		}
		else
			DestroyWindow();
	}
	/*!*************************************************************************
	* \fn Window::Shutdown();
	* \brief Shut down the window and GL Context.
	***************************************************************************/
	void Window::Shutdown()
	{
		glfwTerminate();
	}

	/*!*************************************************************************
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

	/*!*************************************************************************
	* \fn Window::DestroyWindow();
	* \brief Destroy a window instance.
	***************************************************************************/
	void Window::DestroyWindow()
	{
		if (s_window)
		{

		}
	}

	/*!*************************************************************************
	* \fn CreateWindow(int width, int height, const char* name);
	* \brief Callback used when the window is closed.
	* \param window Window that was closed.
	***************************************************************************/
	void WindowCloseCallback(GLFWwindow*)
	{
		Engine::NotifyShutdown();
	}
}