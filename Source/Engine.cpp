/*!*****************************************************************************
* \file Engine.cpp
* \author Lepus
* \brief Manages Orion's engine life cycle (initialization, update, exit).
*******************************************************************************/
#include "Engine.hpp"
#include "Input.hpp"
#include "SceneManager.hpp"
#include "EntityManager.hpp"
#include "ImGuiInterface.hpp"
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
		SceneManager::Load("savefile.scn");
		Cetus::Init(m_window.GetWindow());
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
			Input::Update();
			EntityManager::Update(0.0f);
			Renderer::Update();
			Cetus::Render();
		}
	}

	/*!*************************************************************************
	* \fn void Engine::Shutdown();
	* \brief Clean up engine systems.
	***************************************************************************/
	void Engine::Shutdown()
	{
		SceneManager::Save("savefile.scn");
		Cetus::Shutdown();
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