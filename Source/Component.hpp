/*!*****************************************************************************
* \file Component.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <iostream>
namespace Orion
{
	class Entity;
	/*!*************************************************************************
	* \class Component
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class Component
	{
	public:
		//! Constructor. Called only once, making it good for one-time initial
		//! allocations.
		Component();
		//! Called at least once in the constructor to initialize some
		//! properties. Can be called later upon the reset of this component.
		virtual void Start();
		//! Update this component once every frame.
		virtual void Update(float);
		//! Called at least once in the destructor for basic cleanup. Can be
		//! called later upon the reset of this component.
		virtual void Stop();
		//! Reset the state of this component.
		void Reset();
		//! Get another Component from the Entity to which this belongs.
		template <typename ComponentType>
		ComponentType* Get();
		//! Set the parent Entity of this component. Can only be done once.
		void SetParent(Entity* parent);
		//! Display data in IMGui
		virtual void DisplayImGui();
		//! Serialization
		virtual void Save(std::ostream& os);
		//! Serialization
		virtual void Load(std::istream& is);
		//! Destructor. Called only once, and cleans up any remaining allocated
		//! objects.
		~Component();
	protected:
		//! Entity to which this Component belongs.
		Entity* m_parent{ nullptr };
	};
}