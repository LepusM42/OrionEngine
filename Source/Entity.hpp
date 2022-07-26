/*!*****************************************************************************
* \file Entity.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <vector>
#include <string>
#include "Betel.hpp"
namespace Orion
{
	class Component;
	/*!*************************************************************************
	* \class Entity
	* \brief Used to represent an object in gamespace. Structurally, it's little
	*  more than an aggregation of one or more Components.
	***************************************************************************/
	class Entity
	{
	public:
		//! Does nothing.
		template <typename ComponentType>
		ComponentType* Get()
		{
			for (Component* comp : m_components)
			{
				if (ComponentType* cast = dynamic_cast<ComponentType*>(comp))
				{
					return cast;
				}
			}
			return nullptr;
		}
		//! Does nothing.
		void Add(Component* component);
		//! Does nothing.
		template <typename ComponentType>
		void AddNew()
		{
			if (!Get<ComponentType>())
			{
				ComponentType* newComponent = Betel::Allocate<ComponentType>();
				Add(newComponent);
				newComponent->Start();
			}
		}
		//! Does nothing.
		void Start();
		//! Does nothing.
		void Update(float dt);
		//! Does nothing.
		void Stop();
		//! Mark for destruction
		void Destroy();
		//! Mark for destruction
		bool MarkedForDestruction();
		//! Remove all components
		void ClearComponents();
		//! Display all components in ImGui
		void DisplayComponents();
		//! Serialization
		void Save(std::ostream& sceneFile);
		//! Name of the object
		std::string m_name;
	private:
		//! Map of all components, accessed using each component's unique ID.
		std::vector<Component*> m_components;
		//! Used by manager to delete
		bool m_marked{ false };
	};

	//! Make a new blank entity
	Entity* CreateEntity();
}