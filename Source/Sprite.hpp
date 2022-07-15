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
#include "Texture.hpp"
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
		Texture* GetTexture();
		void SetTexture(Texture* tex);
		Rigel::Vector<float>& GetColor();
		~Sprite();
	private:
		Mesh m_mesh;
		Texture* m_texture{ nullptr };
		Rigel::Vector<float> m_color;
	};
}