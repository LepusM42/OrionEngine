/*!*****************************************************************************
* \file Engine.hpp
* \author Lepus
* \brief Interface for the core process of Orion's engine life cycle.
*******************************************************************************/
#pragma once
#include "Renderer.hpp"
#include "Window.hpp"
namespace Orion
{
	class Renderer;
	class Window;
	/*!*************************************************************************
	* \class Engine
	* \brief Manages the initialization, updating, and cleanup of all Orion
	* systems.
	***************************************************************************/
	class Engine
	{
	public:
		//! Default constructor.
		Engine();
		//! Initialize engine systems.
		void Init();
		//! Update engine systems.
		void Update();
		//! Clean up engine systems.
		void Shutdown();
		//! Tell the engine to initiate the shutdown sequence.
		static void NotifyShutdown();
	private:
		//! The engine runs as long as this is true. Kept static to avoid the
		//! clunky Singleton Pattern.
		static bool s_isUpdating;
		Window m_window;
	};
}