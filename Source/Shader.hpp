/*!*****************************************************************************
* \file Shader.hpp
* \author Lepus
* \brief Loads and executes shader files, which modify vertex data.
*******************************************************************************/
#pragma once
#include "glew.h"
#include <vector>
#include <string>
namespace Orion
{
	/*!*************************************************************************
	* \class ShaderObject
	* \brief Object representing executable shader code, which is to be added
	* to a shader program before it can be used.
	***************************************************************************/
	struct ShaderObject
	{
		//! Constructor for a shader object.
		ShaderObject(const char* filename, GLenum type);
		//! Get the shader's OpenGL ID for compilation and attachment.
		GLuint GetHandle() const;
	private:
		//! Get the contents of a GLSL file.
		std::string LoadShaderFile(std::string filename) const;
		//! Handle of the shader object in OpenGL, used to compile it and 
		//! attach it to a shader program.
		GLuint m_objID{ 0 };
	};

	/*!*************************************************************************
	* \class ShaderProgram
	* \brief Wrapper around a shader program, which executes a number of
	* shader objects that have all been successfully compiled, attached to it,
	* and linked together.
	***************************************************************************/
	class ShaderProgram
	{
	public:
		//! Initialize the shader program.
		void Init();
		//! Use the program
		void Use();
		//! Add a new shader file to the program.
		void AddShader(const char* file, GLenum type);
		//! Retrieve the name of a vertex attribute from the shader program.
		int GetAttribute(const char* attribute) const;
		//! Retrieve the name of a uniform variable from the shader program.
		int GetUniform(const char* uniform) const;
		//! Retrieve the name of a uniform variable from the shader program.
		void GetUniformData(const char* uniform, float* data) const;
		//! Clean up shader objects.
		~ShaderProgram();
	private:
		//! Compile one shader object and attach it to the shader program.
		void CompileShaderSource(ShaderObject shader) const;
		//! Link all compiled shader objects, then validate the program.
		void LinkShaderProgram() const;
		//! OpenGL handle of the shader program.
		GLuint m_shaderProgram{ 0 };
		//! All shader objects attached to the program. Really only used for
		//! detachment from the program in the destructor.
		std::vector<ShaderObject> m_objects;
	};
}