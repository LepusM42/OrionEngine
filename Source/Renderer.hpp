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
	/*!*************************************************************************
	* \class Renderer
	* \brief Renders visual data to a rear buffer, which is displayed after
	* being swapped with the front buffer.
	***************************************************************************/
	class Renderer
	{
	public:
		//! Constructor
		Renderer();
		//! Initialize the renderer.
		void Init();
		//! Update the renderer.
		void Update();
		//! World conversion matrix.
		static Rigel::Matrix<float>& GetWorldMatrix();
		//! Draw something.
		void Draw(Sprite* sprite, Transform* transform);
	private:
		static Rigel::Matrix<float> s_world;
		ShaderProgram m_shader; //!< Used to retrieve shader variables.
	};
}