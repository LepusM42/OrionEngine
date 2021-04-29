/******************************************************************************!
* \file Engine.hpp
* \author Lepus
* \brief Interface for the core process of Orion's engine life cycle.
*******************************************************************************/
#pragma once
namespace Orion
{
	/**************************************************************************!
	* \class Engine
	* \brief Manages the initialization, updating, and cleanup of all Orion
	* systems.
	***************************************************************************/
	class Engine
	{
	public:
		//!< Initialize engine systems.
		static void Init();
		//!< Update engine systems.
		static void Update();
		//!< Clean up engine systems.
		static void Exit();
	private:
	};
}