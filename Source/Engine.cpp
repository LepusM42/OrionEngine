/******************************************************************************!
* \file Engine.cpp
* \author Lepus
* \brief Manages Orion's engine life cycle (initialization, update, exit).
*******************************************************************************/
#include "Engine.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
namespace Orion
{
	/**************************************************************************!
	* \fn void Engine::Init();
	* \brief Initialize engine systems.
	***************************************************************************/
	void Engine::Init()
	{
		Window::Init(800, 600, "Golem Farm");
		//Renderer::Init();
	}

	/**************************************************************************!
	* \fn void Engine::Update();
	* \brief Update engine systems.
	***************************************************************************/
	void Engine::Update()
	{
		while (true);
	}

	/**************************************************************************!
	* \fn void Engine::Exit();
	* \brief Clean up engine systems.
	***************************************************************************/
	void Engine::Exit()
	{
		Window::Shutdown();
	}
}