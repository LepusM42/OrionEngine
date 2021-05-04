/******************************************************************************!
* \file Renderer.cpp
* \author Lepus
* \brief Displays graphics.
*******************************************************************************/
#include "glew.h"
#include "Renderer.hpp"
#include "Rigel.hpp"
#include "Shader.hpp"
#include <iostream>
namespace Orion
{
	/**************************************************************************!
	* \fn void Renderer::Init();
	* \brief Initialize the renderer.
	***************************************************************************/
	void Renderer::Init()
	{
		GLenum retval = glewInit();
		if (retval == GLEW_OK)
		{
			ShaderProgram s;
			s.Init();

			float pos[] = {
				0.0f,0.0f,0.0f,
				-0.5f,0.5f,0.0f,
				0.5f,0.5f,0.0f };
			GLuint VBO; //Buffer object holding vertices.
			glGenBuffers(1, &VBO); //Read a numerical ID into this buffer
			//Declare this buffer as one that holds a vertex array, then
			//bind it to the current context.
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//Fill the bound buffer object with the vertex data, and declare
			//it to be used for static drawing.
   			glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
			//Give this vertex attribute (position) an attribute index of 0.
			glEnableVertexAttribArray(0);
			//After this vertex buffer object has been bound and filled with
			//vertex data, bind it again for drawing since we changed its
			//state.
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
		else
		{
			std::cout << glewGetErrorString(retval) << std::endl;
		}
	}

	/**************************************************************************!
	* \fn void Renderer::Update();
	* \brief Update the renderer.
	***************************************************************************/
	void Renderer::Update()
	{

	}
}