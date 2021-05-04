/******************************************************************************!
* \file Shader.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include "glew.h"
#include <vector>
#include <string>
namespace Orion
{
	struct ShaderSrc
	{
		ShaderSrc(GLuint, int, std::string);
		GLuint m_objID{ 0 };
		int m_length{ 0 };
		std::string m_src;
	};
	/**************************************************************************!
	* \class Shader
	* \brief Template for a class.
	***************************************************************************/
	class Shader
	{
	public:
		Shader() = default;
		//!< Does nothing.
		void Init();
		//!< Does nothing.
		void AddShader(const char* filename, GLenum type);
		std::string GetShader(std::string filename);
		int GetAttribute(const char* attribute);

	private:
		ShaderSrc GetShaderSource(const char* name, GLenum type);
		void CompileShaderSource(ShaderSrc shader);
		void LinkShaderProgram();
		GLuint m_shaderProgram{ 0 };
	};
}