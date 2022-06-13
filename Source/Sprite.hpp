/*!*****************************************************************************
* \file Sprite.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
#include "Mesh.hpp"
#include "Rigel.hpp"
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
		void Start() override;
		void Update(float dt) override;
		void Stop() override;
		Mesh& GetMesh();
		Rigel::Vector<float> GetColor();
		~Sprite();
	private:
		Mesh m_mesh;
		Rigel::Vector<float> m_color;
	};
}