/*!*****************************************************************************
* \file Example.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include "Component.hpp"
#include <list>
#include "Entity.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \class Example
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	static class EntityManager
	{
	public:
		EntityManager();
		static std::vector<Entity*> Pool();
		static void Add(Entity* e);
		static void Update(float dt);
		static void Remove(Entity* e);
		~EntityManager();
	private:
		static std::list<Entity*> m_entityPool;
	} EM;
}