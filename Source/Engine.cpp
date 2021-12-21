/*!*****************************************************************************
* \file Engine.cpp
* \author Lepus
* \brief Manages Orion's engine life cycle (initialization, update, exit).
*******************************************************************************/
#include "Engine.hpp"
#include "SceneManager.hpp"
#include "EntityManager.hpp"
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
		m_window.Init();
		Renderer::Init();
		SceneManager::Load("initialScene.scn");
	}

	/*!*************************************************************************
	* \fn void Engine::Update();
	* \brief Update engine systems.
	***************************************************************************/
	void Engine::Update()
	{
		while (s_isUpdating)
		{
			m_window.Update();
			EntityManager::Update(0.0f);
			Renderer::Update();
		}
	}

	/*!*************************************************************************
	* \fn void Engine::Shutdown();
	* \brief Clean up engine systems.
	***************************************************************************/
	void Engine::Shutdown()
	{
		m_window.Shutdown();
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