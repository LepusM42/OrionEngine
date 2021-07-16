/*!*****************************************************************************
* \file Stub.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Mesh.hpp"
#include "Renderer.hpp"
namespace Orion
{
	/*!*************************************************************************
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
		unsigned int indices[] = {
			0, 1, 2  //Triangle 1 in this Mesh
		};
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	/*!*************************************************************************
	* \fn void Mesh::Update();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	void Mesh::Update()
	{

	}

	/*!*************************************************************************
	* \fn void Mesh::Update();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	GLuint Mesh::GetVArray()
	{
		return m_VAO;
	}

	/*!*************************************************************************
	* \fn void Mesh::Update();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	GLuint Mesh::GetVBuffer()
	{
		return m_VBO;
	}

	/*!*************************************************************************
	* \fn void Mesh::Update();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	GLuint Mesh::GetIBuffer()
	{
		return m_IBO;
	}

	/*!*************************************************************************
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