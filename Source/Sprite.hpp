/*!*****************************************************************************
* \file Sprite.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Sprite
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class Sprite : public Component
	{
	public:
		Sprite();
		void Update(float dt) override;
		~Sprite();
	private:
		void Start() override;
		void Stop() override;
	};
}