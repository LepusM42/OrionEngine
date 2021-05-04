/******************************************************************************!
* \file Shader.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Shader.hpp"
#include <fstream>
#include <iostream>
namespace Orion
{
	ShaderSrc::ShaderSrc(GLuint shader, int size, std::string src) :
		m_objID{ shader },
		m_length{ size },
		m_src{ src }
	{
	}

	//!< Does nothing.
	void Shader::Init()
	{
		//Initialize the shader program by generating an integral ID.
		m_shaderProgram = glCreateProgram();
		//Load, compile, attach, link, and verify shaders.
		AddShader("VertexShader", GL_VERTEX_SHADER);
		AddShader("FragmentShader", GL_FRAGMENT_SHADER);
		LinkShaderProgram();
		//Activate the fully assembled shader program.
		glUseProgram(m_shaderProgram);
	}

	/**************************************************************************!
	* \fn void Foo::Bar();
	* \brief Does nothing.
	* \param foobar Does nothing.
	* \return Value of foobar.
	***************************************************************************/
	void Shader::AddShader(const char* filename, GLenum type)
	{
		//Read shader source of the specified type from file
		ShaderSrc source = GetShaderSource(filename, type);
		//Compile and attach vertex shader to the shader program
		CompileShaderSource(source);
	}

	std::string Shader::GetShader(std::string filename)
	{
		std::ifstream stream(filename);
		std::string buffer{ "" };
		if(stream.is_open())
		{
			while (!stream.eof())
			{
				char str[4096];
				stream.getline(str, 4096);
				buffer += str;
				buffer += '\n';
			}
		}
		return buffer;
	}

	int Shader::GetAttribute(const char* attribute)
	{
		return glGetAttribLocation(m_shaderProgram, attribute);
	}

	ShaderSrc Shader::GetShaderSource(const char* name, GLenum type)
	{
		GLuint shader = glCreateShader(type);
		std::string filepath = ".glsl";
		filepath = name + filepath;
		std::string src = GetShader(filepath);
		const char* sS = src.c_str();
		int srcLen = strlen(sS);
		glShaderSource(shader, 1, &sS, &srcLen);
		return ShaderSrc(shader, srcLen, src.c_str());
	}

	void Shader::CompileShaderSource(ShaderSrc shader)
	{
		//Compile and attach vertex shader
		int success{ 0 };
		glCompileShader(shader.m_objID);
		glGetShaderiv(shader.m_objID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char error[4096];
			glGetProgramInfoLog(m_shaderProgram, 4096, nullptr, error);
			std::cerr << "shader compilation fucked up:" << error << std::endl;
		}
		glAttachShader(m_shaderProgram, shader.m_objID);
	}

	void Shader::LinkShaderProgram()
	{
		//Link and validate all compiled shaders
		int success{ 0 };
		glLinkProgram(m_shaderProgram);
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			char error[4096];
			glGetProgramInfoLog(m_shaderProgram, 4096, nullptr, error);
			std::cerr << "shader linking fucked up:" << error << std::endl;
		}
		glValidateProgram(m_shaderProgram);
	}
}