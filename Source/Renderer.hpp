/*!*****************************************************************************
* \file Renderer.hpp
* \author Lepus
* \brief Displays graphics.
*******************************************************************************/
#pragma once
#include "Rigel.hpp"
#include "Shader.hpp"
namespace Orion
{
	class Sprite;
	class Transform;
	class ShaderProgram;

	struct SpriteTransform
	{
		SpriteTransform(Sprite* s, Transform* t) :
			spr{ s }, trn{ t }
		{

		}
		Sprite* spr{ nullptr };
		Transform* trn{ nullptr };
	};
	/*!*************************************************************************
	* \class Renderer
	* \brief Renders visual data to a rear buffer, which is displayed after
	* being swapped with the front buffer.
	***************************************************************************/
	static class Renderer
	{
	public:
		//! Constructor
		Renderer();
		//! Initialize the renderer.
		static void Init();
		//! Update the renderer.
		static void Update();
		//! World conversion matrix.
		static Rigel::Matrix<float>& GetWorldMatrix();
		//! Draw something.
		static void Draw(Sprite* sprite, Transform* transform);
	private:
		static void Render(Sprite* sprite, Transform* transform);
		static Rigel::Matrix<float> s_world;
		static std::vector<SpriteTransform> m_drawPool;
		static ShaderProgram m_shader; //!< Used to retrieve shader variables.
	} s_renderer;
}