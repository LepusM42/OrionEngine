/*!*****************************************************************************
* \file Example.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "SceneManager.hpp"
#include "EntityManager.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"
#include "ScriptComponent.hpp"
#include <fstream>
namespace Orion
{
	/*!*************************************************************************
	* \fn 
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param 
	* \return 
	***************************************************************************/
	SceneManager::SceneManager()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the constructor to initialize some
	*  properties. Can be called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void SceneManager::Load(std::string name)
	{
		std::ifstream sceneFile(name);
		std::string str;
		Entity* e = nullptr;
		while (!sceneFile.eof())
		{
			sceneFile >> str;
			if (str == "StartObj")
			{
				std::cout << "New Object\n";
				e = Betel::Allocate<Entity>();
			}
			if (str == "EndObj")
			{
				if (!e)
					return;
				EntityManager::Add(e);
				e = nullptr;
			}
			if (str == "Name:")
			{
				if (!e) continue;
				sceneFile >> str;
				e->m_name = str;
				std::cout << "Name: " << e->m_name << "\n";
			}
			if (str == "Sprite")
			{
				LoadComponent<Sprite>(e, sceneFile);
			}
			if (str == "Transform")
			{
				LoadComponent<Transform>(e, sceneFile);
			}
			if (str == "ScriptComponent")
			{
				LoadComponent<ScriptComponent>(e, sceneFile);
			}
		}
	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the destructor for basic cleanup. Can be
	*  called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void SceneManager::Save(std::string name)
	{
		std::ofstream sceneFile(name);
		for (Entity* e : EntityManager::Pool())
		{
			sceneFile << "StartObj\n";
			sceneFile << "Name: " << e->m_name << "\n";
			e->Save(sceneFile);

			sceneFile << "EndObj\n";

		}
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	SceneManager::~SceneManager()
	{
		for (auto e : EntityManager::Pool())
		{
			Betel::Deallocate(e);
		}
		EntityManager::Pool().clear();
	}
}