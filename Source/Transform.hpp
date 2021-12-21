/*!*****************************************************************************
* \file Transform.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
#include "Rigel.hpp"
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

		Rigel::Vector<float>& GetTranslation();
		Rigel::Vector<float>& GetScale();
		float& GetRotation();
	private:
		Rigel::Vector<float> m_translation{ Rigel::Vector<float>(0.0f, 3) };
		Rigel::Vector<float> m_scale{ Rigel::Vector<float>(0.0f, 3) };
		float m_rotation{ 0.0f };
	};
}