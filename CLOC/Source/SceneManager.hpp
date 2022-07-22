/*!*****************************************************************************
* \file Example.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include <map>
namespace Orion
{
	/*!*************************************************************************
	* \class Example
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class Scene
	{

	};

	/*!*************************************************************************
	* \class Example
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	static class SceneManager
	{
	public:
		SceneManager();
		static void Load(std::string name);
		static void Save(std::string name);
		~SceneManager();
	private:
		std::map<std::string, Scene> m_sceneMap;
	} SM;
}