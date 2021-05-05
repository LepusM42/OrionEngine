/******************************************************************************!
* \file Stub.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Mesh.hpp"
namespace Orion
{
	/**************************************************************************!
	* \fn void Mesh::Init();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	void Mesh::Init()
	{
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		float pos[] = {
			0.0f,0.0f,0.0f,
			-0.5f,0.5f,0.0f,
			0.5f,0.5f,0.0f };
		glGenBuffers(1, &m_VBO); //Read a numerical ID into this buffer
		//Declare this buffer as one that holds a vertex array, then
		//bind it to the current context.
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//Fill the bound buffer object with the vertex data, and declare
		//it to be used for static drawing.
		glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
	}

	/**************************************************************************!
	* \fn void Mesh::Update();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	void Mesh::Update()
	{
		//Give this vertex attribute (position) an attribute index of 0.
		glEnableVertexAttribArray(0);
		//After this vertex buffer object has been bound and filled with
		//vertex data, bind it again for drawing since we changed its
		//state.
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//Tell GL how to interpret this buffer.
		//0 - Index of the attribute (position in this case), which we
		//defined earlier as 0.
		//3 - Number of components this attribute has (X,Y,Z=3).
		//float - Type of the data making up this attribute.
		//false - Whether to normalize the data before passing it along.
		//0 - Stride in bytes between instances of the passed data.
		//nullptr - Offset inside the buffer at which to find the
		//attribute.
		int attr_Pos = 0;// s.GetAttribute("position");
		glVertexAttribPointer(attr_Pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		//Draw a series of points, starting at index 0, drawing 1 point.
		//glDrawArrays draws in order, as opposed to indexed drawing.
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//Disable the attribute at index 0.
		glDisableVertexAttribArray(0);
	}

	/**************************************************************************!
	* \fn Mesh::~Mesh();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}
}