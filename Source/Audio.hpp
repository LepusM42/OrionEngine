/*!*****************************************************************************
* \file Audio.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Audio
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class Audio : public Component
	{
	public:
		Audio();
		void Start() override;
		void Update(float dt) override;
		void Stop() override;
		~Audio();
	private:
	};
}