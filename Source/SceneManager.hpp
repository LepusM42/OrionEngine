/*!*****************************************************************************
* \file Example.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include <map>
#include "Betel.hpp"
#include "Entity.hpp"
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
		template<typename ComponentType>
		static void LoadComponent(Entity* entity, std::istream& sceneFile)
		{
			ComponentType* component = Betel::Allocate<ComponentType>();
			if (!entity || !component) return;
			component->Load(sceneFile);
			entity->Add(component);
			component->Start();
		}
	} SM;
}