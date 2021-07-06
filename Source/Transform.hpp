/*!*****************************************************************************
* \file Transform.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Transform
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class Transform : public Component
	{
	public:
		Transform();
		void Start() override;
		void Update(float dt) override;
		void Stop() override;
		~Transform();
	private:
	};
}