/*!*****************************************************************************
* \file Stub.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include "glfw3.h"
#include <array>
namespace Orion
{
	namespace Input
	{
		//! Does nothing.
		void Update();
		//! Does nothing.
		void SendEvent(int keyCode, int event);
		//! Does nothing.
		int GetEvent(int keyCode);
		//! Does nothing.
		bool isPressed(int keyCode);
		//! Does nothing.
		bool isHeld(int keyCode);
		//! Does nothing.
		bool isReleased(int keyCode);
	}
}