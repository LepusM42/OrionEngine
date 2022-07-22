/*!*****************************************************************************
* \file Renderer.cpp
* \author Lepus
* \brief Displays graphics.
*******************************************************************************/
#include "glew.h"
#include "Sprite.hpp"
#include "Transform.hpp"
#include "Renderer.hpp"
#include "Rigel.hpp"
#include <iostream>
namespace Orion
{
	Rigel::Matrix<float> Renderer::s_world(4);
	std::vector<SpriteTransform> Renderer::m_drawPool;
	ShaderProgram Renderer::m_shader; //!< Used to retrieve shader variables.

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
		for (auto d : m_drawPool)
		{
			Render(d.spr, d.trn);
		}
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
		m_drawPool.push_back(SpriteTransform(sprite, transform));
	}

	/*!*************************************************************************
	* \fn void Draw(Sprite* sprite, Transform* transform);
	* \brief Draw something.
	* \param sprite Visual data (texture, mesh, transparency, etc.)
	* \param transform Spatial data (e.g. position, rotation, size) of the
	*  object to be drawn.
	***************************************************************************/
	void Renderer::Render(Sprite* sprite, Transform* transform)
	{
		//Bail on bad input data
		if (!sprite || !transform) return;
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

		//Bind position to shader position
		int attr_Pos = m_shader.GetAttribute("position");
		glVertexAttribPointer(attr_Pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		//glVertexAttrib3f(attr_Pos, pos[0], pos[1], pos[2]);

		int attr_Col = m_shader.GetAttribute("baseColor");
		glVertexAttribPointer(attr_Col, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3 * sizeof(float)));
		glVertexAttrib3f(attr_Col, sprite->GetColor()[0], sprite->GetColor()[1], sprite->GetColor()[2]);

		int attr_texCoord = m_shader.GetAttribute("vertexTexture");
		glVertexAttribPointer(attr_texCoord, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
		glEnableVertexAttribArray(attr_texCoord);

		float posVec[3] = { transform->GetTranslation()[0], transform->GetTranslation()[1], transform->GetTranslation()[2] };
		m_shader.GetUniformData("posVec", posVec);

		m_shader.GetUniformMatrix("transMat", transform->GetMatrix());

		//Bind world matrix to the world matrix held in the shader
		m_shader.GetUniformMatrix("gWorld", Renderer::GetWorldMatrix());

		//Bind texture
		if (Texture* tex = sprite->GetTexture())
		{
			m_shader.BindTexture(tex, 1);
		}

		//Do the drawing
		glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh().GetNumVertices());

		//Unbind texture

		//Disable the attribute at index 0.
		glDisableVertexAttribArray(attr_Pos);
	}
}