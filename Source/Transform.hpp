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
		void Update(float dt) override;
		~Transform();
	private:
		void Start() override;
		void Stop() override;
	};
}