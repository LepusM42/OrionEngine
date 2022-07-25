/*!*****************************************************************************
* \file Stub.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include "glew.h"
#include "Shader.hpp"
#include "Rigel.hpp"
namespace Orion
{
	typedef Rigel::Vector<float> Vertex;
	/*!*************************************************************************
	* \class Foo
	* \brief Template for a class.
	***************************************************************************/
	struct Triangle
	{
		Triangle(Vertex v1, Vertex v2, Vertex v3) : m_v1{ v1 }, m_v2{ v2 }, m_v3{ v3 }
		{

		}
		Vertex m_v1, m_v2, m_v3;
	};
	/*!*************************************************************************
	* \class Foo
	* \brief Template for a class.
	***************************************************************************/
	class Mesh
	{
	public:
		void Init();
		void Update();
		GLuint GetVArray();
		GLuint GetVBuffer();
		unsigned GetNumVertices();
		void AddTriangle(Vertex v1, Vertex v2, Vertex v3);
		std::vector<Triangle> GetTriangles();
		~Mesh();
	private:
		void AddVertex(Vertex v);
		void InitVertexArray();
		void InitVertexBuffer();
		GLuint m_VAO{ 0 };      //!< Vertex array object holding vertices.
		GLuint m_VBO{ 0 };      //!< Buffer object holding raw vertex data.
		unsigned m_vertexNum{ 0 };
		std::vector<float> m_coords;
		std::vector<Triangle> m_triangles;
	};
}