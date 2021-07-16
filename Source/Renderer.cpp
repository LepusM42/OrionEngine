/*!*****************************************************************************
* \file Renderer.cpp
* \author Lepus
* \brief Displays graphics.
*******************************************************************************/
#include "glew.h"
#include "Sprite.hpp"
#include "Renderer.hpp"
#include "Rigel.hpp"
#include <iostream>
namespace Orion
{
	Sprite spr;
	Rigel::Matrix<float> Renderer::s_world(4);
	static float m_scale{ 0.0f };

	//! Constructor
	Renderer::Renderer()
	{

	}

	/*!*************************************************************************
	* \fn void Renderer::Init();
	* \brief Initialize the renderer.
	***************************************************************************/
	void Renderer::Init()
	{
		GLenum retval = glewInit();
		if (retval == GLEW_OK)
		{
			m_shader.Init();
			spr.Start();
			spr.GetMesh().Init();
		}
		else
		{
			std::cout << glewGetErrorString(retval) << std::endl;
		}
	}

	/*!*************************************************************************
	* \fn void Renderer::Update();
	* \brief Update the renderer.
	***************************************************************************/
	void Renderer::Update()
	{
		spr.Update(0.0f);
		Draw(&spr, 0);
	}

	/*!*************************************************************************
	* \fn Rigel::Matrix<float> GetWorldMatrix();
	* \brief World conversion matrix.
	* \return A matrix used to convert world to screen coordinates.
	***************************************************************************/
	Rigel::Matrix<float>& Renderer::GetWorldMatrix()
	{
		return s_world;
	}

	/*!*************************************************************************
	* \fn void Draw(Sprite* sprite, Transform* transform);
	* \brief Draw something.
	* \param sprite Visual data (texture, mesh, transparency, etc.)
	* \param transform Spatial data (e.g. position, rotation, size) of the
	*  object to be drawn.
	***************************************************************************/
	void Renderer::Draw(Sprite* sprite, Transform* transform)
	{
		//Give this vertex attribute (position) an attribute index of 0.
		glEnableVertexAttribArray(0);
		//After this vertex buffer object has been bound and filled with
		//vertex data, bind it again for drawing since we changed its
		//state.
		glBindBuffer(GL_ARRAY_BUFFER, sprite->GetMesh().GetVBuffer());
		//Tell GL how to interpret this buffer.
		//0 - Index of the attribute (position in this case), which we
		//defined earlier as 0.
		//3 - Number of components this attribute has (X,Y,Z=3).
		//float - Type of the data making up this attribute.
		//false - Whether to normalize the data before passing it along.
		//0 - Stride in bytes between instances of the passed data.
		//nullptr - Offset inside the buffer at which to find the
		//attribute.

		int attr_Pos = m_shader.GetAttribute("position");
		glVertexAttribPointer(attr_Pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		int uni_Scale = m_shader.GetUniform("scale");
		glUniform1f(uni_Scale, (m_scale));
		m_scale += .001f;

		Renderer::GetWorldMatrix()[0][0] = cosf(m_scale);
		Renderer::GetWorldMatrix()[0][1] = -sinf(m_scale);
		Renderer::GetWorldMatrix()[1][0] = sinf(m_scale);
		Renderer::GetWorldMatrix()[1][1] = cosf(m_scale);
		int uni_World = m_shader.GetUniform("gWorld");
		glUniformMatrix4fv(uni_World, 1, GL_TRUE, Renderer::GetWorldMatrix()[0]);
		float matVal[16];
		m_shader.GetUniformData("gWorld", matVal);

		//Draw a series of points, starting at index 0, drawing 1 point.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->GetMesh().GetIBuffer());
		//Draw in triangle mode
		//Draw 3 indices
		//Each index is an unsigned int
		//Byte offset 0
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//Disable the attribute at index 0.
		glDisableVertexAttribArray(0);
	}
}