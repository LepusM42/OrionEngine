/******************************************************************************!
* \file Shader.cpp
* \author Lepus
* \brief Loads and executes shader files, which modify vertex data.
*******************************************************************************/
#include "Shader.hpp"
#include <fstream>
#include <iostream>
namespace Orion
{
	/**************************************************************************!
	* \fn ShaderObject::ShaderObject(const char* name, GLenum type);
	* \brief Constructor for a shader object.
	* \param filename Name of the GLSL file containing the needed shader code.
	* \param type Enumerated type of shader to read, such as GL_VERTEX_SHADER.
	***************************************************************************/
	ShaderObject::ShaderObject(const char* filename, GLenum type)
	{
		m_objID = glCreateShader(type);
		std::string source = LoadShaderFile(filename);
		const char* shaderSource = source.c_str();
		int length = strlen(shaderSource);
		glShaderSource(m_objID, 1, &shaderSource, &length);
	}

	/**************************************************************************!
	* \fn GLuint ShaderObject::GetHandle() const;
	* \brief Get the shader's OpenGL ID for compilation and attachment.
	* \return Shader's unique OpenGL handle.
	***************************************************************************/
	GLuint ShaderObject::GetHandle() const
	{
		return m_objID;
	}

	/**************************************************************************!
	* \fn std::string ShaderObject::LoadShaderFile(std::string filename);
	* \brief Get the contents of a GLSL file.
	* \param filename Name of the GLSL file to load from disk.
	* \return GLSL source code contained in the specified file.
	***************************************************************************/
	std::string ShaderObject::LoadShaderFile(std::string filename) const
	{
		std::ifstream stream(filename);
		std::string buffer{ "" };
		if (stream.is_open())
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

	/**************************************************************************!
	* \fn void ShaderProgram::Init();
	* \brief Initialize the shader program.
	***************************************************************************/
	void ShaderProgram::Init()
	{
		//Initialize the shader program by generating an integral ID.
		m_shaderProgram = glCreateProgram();
		//Add any necessary shader objects to the shader program.
		AddShader("VertexShader.glsl", GL_VERTEX_SHADER);
		AddShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
		//Link all compiled shaders.
		LinkShaderProgram();
		Use();
	}

	void ShaderProgram::Use()
	{
		//Activate the fully assembled shader program.
		glUseProgram(m_shaderProgram);
	}

	/**************************************************************************!
	* \fn void ShaderProgram::AddShader(const char* file, GLenum type) const;
	* \brief Add a new shader file to the program, then attempt to compile it.
	* Upon successful compilation, this shader will be attached to the shader
	* program.
	* \param file Name of the shader file to read from.
	* \param type Enumerated type of shader to read, such as GL_VERTEX_SHADER.
	***************************************************************************/
	void ShaderProgram::AddShader(const char* file, GLenum type)
	{
		//Read shader source code of the specified shader type from a file.
		ShaderObject source(file, type);
		//Compile and attach the shader to the shader program.
		CompileShaderSource(source);
		m_objects.push_back(source);
	}

	/**************************************************************************!
	* \fn int ShaderProgram::GetAttribute(const char* attribute);
	* \brief Retrieve the name of a vertex attribute from the shader program.
	* \param attribute Name of the attribute to retrieve from the program.
	* \return Index of the attribute in the vertex buffer.
	***************************************************************************/
	int ShaderProgram::GetAttribute(const char* attribute) const
	{
		return glGetAttribLocation(m_shaderProgram, attribute);
	}

	/**************************************************************************!
	* \fn int ShaderProgram::GetUniform(const char* uniform);
	* \brief Retrieve the name of a uniform variable from the shader program.
	* \param uniform Name of the uniform to retrieve from the program.
	* \return Index of the uniform in the vertex buffer.
	***************************************************************************/
	int ShaderProgram::GetUniform(const char* uniform) const
	{
		return glGetUniformLocation(m_shaderProgram, uniform);
	}

	//! Retrieve the name of a uniform variable from the shader program.
	void ShaderProgram::GetUniformData(const char* uniform, float* data) const
	{
		GLuint uniformName = glGetUniformLocation(m_shaderProgram, uniform);
		glGetUniformfv(m_shaderProgram, uniformName, data);
	}

	/**************************************************************************!
	* \fn void ShaderProgram::CompileShaderSource(ShaderObject shader);
	* \brief Compile one shader object and attach it to the shader program.
	* \param shader Structure representing a shader object, including its source
	* code and unique integral handle (used to attach to the program).
	***************************************************************************/
	void ShaderProgram::CompileShaderSource(ShaderObject shader) const
	{
		//Attempt to compile the passed in shader object.
		int success{ 0 };
		glCompileShader(shader.GetHandle());
		//Log any errors that may have occurred during compilation.
		glGetShaderiv(shader.GetHandle(), GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char error[4096];
			glGetProgramInfoLog(m_shaderProgram, 4096, nullptr, error);
			std::cerr << "shader compilation fucked up:" << error << std::endl;
			return;
		}
		//After successful compilation, attach the shader object to the shader
		//program.
		glAttachShader(m_shaderProgram, shader.GetHandle());
	}

	/**************************************************************************!
	* \fn void ShaderProgram::LinkShaderProgram();
	* \brief Link all compiled shader objects, then validate the program.
	***************************************************************************/
	void ShaderProgram::LinkShaderProgram() const
	{
		//Link all compiled shaders.
		int success{ 0 };
		glLinkProgram(m_shaderProgram);
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		//Log any errors that may have occurred during linking.
		if (!success)
		{
			char error[4096];
			glGetProgramInfoLog(m_shaderProgram, 4096, nullptr, error);
			std::cerr << "shader linking fucked up:" << error << std::endl;
			return;
		}
		//Validate the shader program after linking to ensure that it is ready
		//for use.
		glValidateProgram(m_shaderProgram);
	}

	/**************************************************************************!
	* \fn void ShaderProgram::~ShaderProgram();
	* \brief Clean up shader objects.
	***************************************************************************/
	ShaderProgram::~ShaderProgram()
	{
		for (ShaderObject shader : m_objects)
		{
			glDetachShader(m_shaderProgram, shader.GetHandle());
			glDeleteShader(shader.GetHandle());
		}
		glDeleteProgram(m_shaderProgram);
	}
}