/*!*****************************************************************************
* \file Behavior.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Behavior
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class Behavior : public Component
	{
	public:
		Behavior();
		void Start() override;
		void Update(float dt) override;
		void Stop() override;
		~Behavior();
	private:
	};
}