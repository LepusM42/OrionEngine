/*!*****************************************************************************
* \file Stub.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Mesh.hpp"
#include "Renderer.hpp"
#include <vector>
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
		InitVertexArray();
		InitVertexBuffer();
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
	unsigned Mesh::GetNumVertices()
	{
		return m_vertexNum;
	}

	/*!*************************************************************************
	* \fn void Mesh::AddTriangle(Vertex v1, Vertex v2, Vertex v3);
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \param foobar Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	void Mesh::AddTriangle(Vertex v1, Vertex v2, Vertex v3)
	{
		AddVertex(v1);
		AddVertex(v2);
		AddVertex(v3);
	}

	/*!*************************************************************************
	* \fn Mesh::~Mesh();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	Mesh::~Mesh()
	{
		if (m_VBO)
		{
			glDeleteBuffers(1, &m_VBO);
		}
		if (m_VAO)
		{
			glDeleteVertexArrays(1, &m_VAO);
		}
	}
	
	/*!*************************************************************************
	* \fn Mesh::~Mesh();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	void Mesh::AddVertex(Vertex v)
	{
		++m_vertexNum;
		for (unsigned i = 0; i < v.size(); ++i)
		{
			m_coords.push_back(v[i]);
		}
	}

	/*!*************************************************************************
	* \fn Mesh::~Mesh();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	void Mesh::InitVertexArray()
	{
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
	}

	/*!*************************************************************************
	* \fn Mesh::~Mesh();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	void Mesh::InitVertexBuffer()
	{
		//Read a numerical ID into this buffer
		glGenBuffers(1, &m_VBO);
		//Declare this buffer as one that holds a vertex array, then
		//bind it to the current context.
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//Fill the bound buffer object with the vertex data, and declare
		//it to be used for static drawing.
		size_t bufSize = m_coords.size() * sizeof(m_coords.front());
		glBufferData(GL_ARRAY_BUFFER, bufSize, m_coords.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glFinish();
	}
}