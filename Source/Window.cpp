/******************************************************************************!
* \file Window.cpp
* \author Lepus
* \brief Creates and manages the application window.
*******************************************************************************/
#include <glew.h>
#include "Window.hpp"
#include "Engine.hpp"
#include "Rigel.hpp"
#include <iostream>
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
			glfwMakeContextCurrent(s_window);
			glfwSetWindowCloseCallback(s_window, WindowCloseCallback);
			GLenum retval = glewInit();
			if (retval == GLEW_OK)
			{
				Rigel::Vector<float> vertex[1] = { Rigel::Vector<float>(0.0f, 3) };
				GLuint VBO;
				//unsigned flags = 0;
				//flags | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT;
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				size_t t = sizeof(vertex);
				glBufferData(GL_ARRAY_BUFFER, t, vertex, GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
				glDrawArrays(GL_POINTS, 0, 1);
			}
			else
			{
				std::cout << glewGetErrorString(retval) << std::endl;
			}
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