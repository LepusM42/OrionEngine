/*!*****************************************************************************
* \file Engine.cpp
* \author Lepus
* \brief Manages Orion's engine life cycle (initialization, update, exit).
*******************************************************************************/
#include "Engine.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
namespace Orion
{
	//Initialize the static boolean that runs the engine
	bool Engine::s_isUpdating{ true };

	/*!*************************************************************************
	* \fn void Engine::Engine();
	* \brief Default constructor.
	***************************************************************************/
	Engine::Engine()
	{

	}

	/*!*************************************************************************
	* \fn void Engine::Init();
	* \brief Initialize engine systems.
	***************************************************************************/
	void Engine::Init()
	{
		Window::Init();
		Renderer::Init();
	}

	/*!*************************************************************************
	* \fn void Engine::Update();
	* \brief Update engine systems.
	***************************************************************************/
	void Engine::Update()
	{
		while (s_isUpdating)
		{
			Window::Update();
			Renderer::Update();
		}
	}

	/*!*************************************************************************
	* \fn void Engine::Shutdown();
	* \brief Clean up engine systems.
	***************************************************************************/
	void Engine::Shutdown()
	{
		Window::Shutdown();
	}

	/*!*************************************************************************
	* \fn void Engine::NotifyShutdown();
	* \brief Tell the engine to initiate the shutdown sequence.
	***************************************************************************/
	void Engine::NotifyShutdown()
	{
		s_isUpdating = false;
	}
}