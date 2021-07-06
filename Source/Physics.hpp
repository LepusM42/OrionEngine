/*!*****************************************************************************
* \file Physics.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Physics
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class Physics : public Component
	{
	public:
		Physics();
		void Start() override;
		void Update(float dt) override;
		void Stop() override;
		~Physics();
	private:
	};
}