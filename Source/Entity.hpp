/*!*****************************************************************************
* \file Entity.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <vector>
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
		void Start();
		//! Does nothing.
		void Update(float dt);
		//! Does nothing.
		void Stop();
	private:
		//! Map of all components, accessed using each component's unique ID.
		std::vector<Component*> m_components;
	};
}