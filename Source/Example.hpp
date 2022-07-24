/*!*****************************************************************************
* \file Example.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Example
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class Example : public Component
	{
	public:
		Example();
		void Update(float dt) override;
		void DisplayComponents();
		~Example();
	private:
		void Start() override;
		void Stop() override;
	};
}