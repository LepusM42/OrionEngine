/*!*****************************************************************************
* \file Stub.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Input.hpp"
#include <iostream>
#define KEY_OFF -1
namespace Orion
{
	namespace Input
	{
		/*!*************************************************************************
		* \class
		* \brief
		***************************************************************************/
		class InputManager
		{
		public:
			//! Does nothing.
			void Update();
			//! Does nothing.
			void SendKeyEvent(int keyCode, int event);
			//! Does nothing.
			int GetKeyEvent(int keyCode);
		private:
			//! Does nothing.
			std::array<int, GLFW_KEY_LAST> m_keys;
		};
		//! Does nothing.
		InputManager input;

		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		void InputManager::Update()
		{

		}
		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		void InputManager::SendKeyEvent(int keyCode, int event)
		{
			m_keys[keyCode] = event;
		}
		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		int InputManager::GetKeyEvent(int keyCode)
		{
			return m_keys[keyCode];
		}

		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		void Update()
		{
			input.Update();
		}
		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		void SendEvent(int keyCode, int event)
		{
			input.SendKeyEvent(keyCode, event);
		}
		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		int GetEvent(int keyCode)
		{
			return input.GetKeyEvent(keyCode);
		}
		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		bool isPressed(int keyCode)
		{
			return GetEvent(keyCode) == GLFW_PRESS;
		}
		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		bool isHeld(int keyCode)
		{
			return GetEvent(keyCode) == GLFW_REPEAT;
		}
		/*!*************************************************************************
		* \fn
		* \brief
		* \param
		* \return
		***************************************************************************/
		bool isReleased(int keyCode)
		{
			return GetEvent(keyCode) == GLFW_RELEASE;
		}
	}
}